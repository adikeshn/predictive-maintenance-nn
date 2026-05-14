from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
import ctypes

lib = ctypes.CDLL('maintenance_net.so')
lib.predict_percent.argtypes = [ctypes.POINTER(ctypes.c_double)]
lib.predict_percent.restype = ctypes.c_double
lib.predict_category.argtypes = [ctypes.POINTER(ctypes.c_double)]
lib.predict_category.restype = ctypes.c_int

class MachineData(BaseModel):
    return_percent: bool = True
    air_temp: float = 0.0
    process_temp: float = 0.0
    rot_speed: float = 0.0
    torque: float = 0.0
    tool_wear: float = 0.0

class ModelPrediction(BaseModel):
    failure_percent: float = 0.0
    failure_class: int = 0

api = FastAPI()

def get_input_array(data: MachineData):
    data_arr = [data.air_temp, data.process_temp, data.rot_speed, data.torque, data.tool_wear]
    return (ctypes.c_double * len(data_arr))(*data_arr)

@api.get("/")
def init():
    return "machine failure model"

@api.post("/predict")
def predict(data: MachineData) -> ModelPrediction:
    try:
        inp = get_input_array(data)
        if data.return_percent:
            percent = lib.predict_percent(inp)
            return ModelPrediction(failure_percent=percent, failure_class=-1)
        else:
            category = lib.predict_category(inp)
            return ModelPrediction(failure_percent=-1.0, failure_class=category)
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))
    
