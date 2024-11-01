from pydantic import BaseModel
from typing import List
from typing import Optional


class Command(BaseModel):
    command_type: str
    command_name: Optional[str] = None
    free_command: Optional[str] = None
    expression: Optional[str] = None
    parameters: Optional[list[str]] = []
