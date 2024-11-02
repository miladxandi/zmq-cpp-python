# ZeroMQ Project (C++ & Python)

[Read about server](#server) - [Read about client](#client)

## Fast installation:

### 1. Run this command:
```
docker compose -f .\docker-compose.yml -p zmq-project up -d
```

### 2. Open this url to verify it`s running:
```
http://localhost:8080/
```

### 3. Send request to this url:

#### For OS:
```
{
	"command_type":"os",
	"command_name":"ping",
	"parameters":["google.com","-c","2"]
}
```

#### For Compute:
```
{
    "command_type":"compute",
    "expression":"( 2 + 2 ) * 10"
}
```

#### Send`POST`rquest to this URL: 
```
http://localhost:8080/execute
```
## Server:
- Language: Python
- Versions: 3.9 - 3.12
- OS: Ubuntu 22.04
- Packages:
  - "annotated-types/0.7.0"
  - "cffi/1.17.1"
  - "pycparser/2.22"
  - "pydantic/2.9.2"
  - "pydantic_core/2.23.4"
  - "pyzmq/26.2.0"
  - "typing_extensions/4.12.2"
  - "zmq/0.0.0"
  - "zmqpy/0.3.3.2"

### Why Python?
Rather than relying on my preferred technologies because of undefined project specs about required technologies, I started this part based on my job position.
The only reason to doing this with python is the job position related tasks.

### Description
I recommend to run it on Docker or an Ubuntu OS machine for better experience and to reduce the failure rate.
As you described in the RFP it will get the both types of commands and after a little process data will send into the server from ZeroMQ protocol.

### Run Server

```
cd server/
docker build --tag "Server" .
```



## Client:
- Language: C++
- Versions: 17
- Cmake: 3.26.6
- Compiler: Ninja
- OS: Ubuntu 22.04
- Packages:
  - "crowcpp-crow/1.2.0"
  - "asio/1.29.0"
  - "zmqpp/4.2.0"
  - "nlohmann_json/3.2.0"

### Why C++?
- Super 
- Truly cross-platform
- Easily run on edge devices
- Zero environment dependency
- Lightweight and small size
- Variety of build options for any CPU arch

### Description
I recommend to run it on Docker or an Ubuntu OS machine for better experience and to reduce the failure rate.
As you described in the RFP it will get the both types of commands and after a little process data will send into the server from ZeroMQ protocol.

### Run client

```
docker build --tag "Client" .
```

### Known issues:
- Downloading libraries: Conan is dependency manager for C++ and it restricted Iranians even with Shecan or 403.online, please use VPN (not proxies) with TUN Mode (system-wide VPN) enabled
- Build errors: We cannot build the client code on Windows OS machines because of libzmq3 is a Linux-dependent lib
- Run errors: The entire client project cannot run on some Arm-64 arch devices.

Any other bugs? reach me at [miladxandi@icloud.com](mailto:miladxandi@icloud.com)