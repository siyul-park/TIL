# 첫번째 gRPC 프로그램



우선 protobuf 를 정의하자

```protobuf
syntax = "proto3";

package employee;

service Employee {
  rpc getDetails (EmployeeRequest) returns (EmployeeResponse) {}
}

message EmployeeRequest {
  int32 id = 1;
}

message EmployeeResponse{
  EmployeeDetails message = 1;
}

message EmployeeDetails {
  int32 id = 1;
  string email = 2;
  string firstName = 3;
  string lastName = 4;
}
```

employee.proto



그리고 이것을 컴파일을 해야 한다. Node.js + typescript 를 사용할 것이기 때문에 [ts-protoc-gen](https://www.npmjs.com/package/ts-protoc-gen) 과 [grpc-tools](https://www.npmjs.com/package/grpc-tools) 그리고 [grpc_tools_node_protoc_ts](https://www.npmjs.com/package/grpc_tools_node_protoc_ts) 를 설치하자. 

기본적으로 proto 파일을 빌드 할수 있는 스크립트를 제공하지 않기 때문에 스크립트를 작성을 해야 한다. shelljs를 사용해서 js 파일로 스크립트를 작성한다



```javascript
const path = require("path");
const shell = require("shelljs");
const rimraf = require("rimraf");

// https://github.com/shelljs/shelljs/issues/469
process.env.PATH += (path.delimiter + path.join(process.cwd(), "../", "../", "../node_modules", ".bin"));

const PROTO_DIR = path.join(__dirname, "../proto");
const MODEL_DIR = path.join(__dirname, "../generated");
const PROTOC_GEN_TS_PATH = path.join(__dirname, "../", "../", "../node_modules/.bin/protoc-gen-ts");

shell.exec(`mkdir ${MODEL_DIR}`)

rimraf.sync(`${MODEL_DIR}/*`);

const protoConfig = [
  `--plugin="protoc-gen-ts=${PROTOC_GEN_TS_PATH}" `,
  `--grpc_out="grpc_js:${MODEL_DIR}" `,
  `--js_out="import_style=commonjs,binary:${MODEL_DIR}" `,
  `--ts_out="grpc_js:${MODEL_DIR}" `,
  `--proto_path ${PROTO_DIR} ${PROTO_DIR}/*.proto`
];

// https://github.com/agreatfool/grpc_tools_node_protoc_ts/tree/master/examples
shell.exec(`grpc_tools_node_protoc ${protoConfig.join(" ")}`);

// https://github.com/dcodeIO/protobuf.js#command-line
// https://github.com/dcodeIO/protobuf.js#command-line-apis
```



그리고 package.json 에 스크립트를 추가해주자

```json
"prebuild": "npm run build:proto",
"build": "npm run clean && npm run compile",
"build:proto": "node bin/proto",
```



npm run build 를 하면 정상적으로 gernerated 파일이 생성이 되는것을 확인할 수 있다.

이제 실제로 protobuf 를 구현을 해보자

```typescript
import {
  sendUnaryData,
  ServerUnaryCall,
  UntypedHandleCall,
} from "@grpc/grpc-js";
import _ from "lodash";
import jsonfile from "jsonfile";
import path from "path";
import {
  EmployeeDetails,
  EmployeeRequest,
  EmployeeResponse,
} from "../../generated/employee_pb";
import { IEmployeeServer } from "../../generated/employee_grpc_pb";

class Employee implements IEmployeeServer {
  [method: string]: UntypedHandleCall;

  private readonly data = jsonfile.readFileSync(
    path.join(__dirname, "../../data.json")
  );

  getDetails(
    call: ServerUnaryCall<EmployeeRequest, EmployeeResponse>,
    callback: sendUnaryData<EmployeeResponse>
  ): void {
    const response = new EmployeeResponse();

    const employee = _.find(this.data, { id: call.request.getId() });
    const employeeDetails = new EmployeeDetails();
    if (employee != null) {
      employeeDetails.setId(employee.id);
      employeeDetails.setEmail(employee.email);
      employeeDetails.setFirstname(employee.firstname);
      employeeDetails.setLastname(employee.lastname);
    }

    response.setMessage(employeeDetails);

    callback(null, response);
  }
}

export default Employee;
```

생성된 employee_grpc_pb 를 이용해서 Employee 객체를 구현한다. proto엔 

```protobuf
service Employee {
  rpc getDetails (EmployeeRequest) returns (EmployeeResponse) {}
}
```

로 정의가 되어 있었다.



그리고 구현한 서비스를 이용해서 server 를 만들어 보자

```typescript
import { Server, ServerCredentials } from "@grpc/grpc-js";
import { EmployeeService } from "../generated/employee_grpc_pb";
import { Employee } from "./service";

function main() {
  const server = new Server({
    "grpc.max_receive_message_length": -1,
    "grpc.max_send_message_length": -1,
  });

  server.addService(EmployeeService, new Employee());
  server.bindAsync(
    "0.0.0.0:50051",
    ServerCredentials.createInsecure(),
    (error) => {
      if (error != null) {
        throw error;
      }
      server.start();
    }
  );
}

main();
```



50051에 서버를 바인딩했다. 이제 클라이언트쪽을 작업 해보자.



```typescript
import { credentials } from "@grpc/grpc-js";
import { EmployeeClient } from "../generated/employee_grpc_pb";
import { EmployeeRequest, EmployeeResponse } from "../generated/employee_pb";

const client = new EmployeeClient(
  "localhost:50051",
  credentials.createInsecure(),
  {
    "grpc.keepalive_time_ms": 120000,
    "grpc.http2.min_time_between_pings_ms": 120000,
    "grpc.keepalive_timeout_ms": 20000,
    "grpc.http2.max_pings_without_data": 0,
    "grpc.keepalive_permit_without_calls": 1,
  }
);

function getDetails(request: EmployeeRequest): Promise<EmployeeResponse> {
  return new Promise<EmployeeResponse>((resolve, reject) => {
    client.getDetails(request, (error, response) => {
      if (error != null) {
        return reject(error);
      }
      return resolve(response);
    });
  });
}

async function run() {
  const request = new EmployeeRequest();
  request.setId(1);
  await getDetails(request);
}

run().then(() => {});
```

좀더 사용하기 쉽게 callback 을 promise 로 래핑을 했다.



모든 코드는 https://github.com/siyual-park/gRPC-study/tree/master/examples/hello-world 에서 볼수 있다