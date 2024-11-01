import json
import time
import zmq
import subprocess
import logging
from models.Command import Command
from helpers.Functions import generator

# تنظیمات logging
logging.basicConfig(
    filename='server.log',
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s'
)

try:
    logging.info("Server started...")
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    socket.bind("tcp://*:5510")
    logging.info("Service bound to port 5510")

    while True:
        try:
            # انتظار برای دریافت درخواست از کلاینت
            message = socket.recv().decode("utf-8")
            logging.info(f"Received request: {message}")

            jsonValue = json.loads(message)
            command = Command(**jsonValue)

            result = "Undefined"
            error = None
            syntax = None

            if command.command_type == "os":
                parameters = " ".join(command.parameters)
                syntax = f"{command.command_name} {parameters}"

            elif command.command_type == "compute":
                syntax = f"echo $(( {command.expression} ))"

            else:
                syntax = f"{command.free_command}"

            process = subprocess.Popen(
                syntax,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                shell=True,
            )
            result, error = process.communicate()
            time.sleep(1)

            if error:
                response = json.dumps(generator(None, "Execution layer", False, 500, error.strip()))
                logging.error(f"Error executing command: {error.strip()}")
            else:
                response = json.dumps(generator(result.strip(), "Execution layer", True))
                logging.info(f"Command executed successfully: {result.strip()}")

            socket.send_string(response)
            logging.info(f"Response sent: {response}")

        except ValueError as error:
            error_message = f"Only accepts JSON format! {str(error)}"
            response = json.dumps(generator(None, "Exceptions layer", False, 500, error_message))
            socket.send_string(response)
            logging.error(error_message)

        except Exception as error:
            response = json.dumps(generator(None, "Exceptions layer", False, 500, str(error)))
            socket.send_string(response)
            logging.error(f"Unexpected error: {error}")

except Exception as error:
    logging.critical(f"Critical error in server startup: {error}")
