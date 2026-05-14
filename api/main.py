from fastapi import FastAPI, HTTPException
from pathlib import Path
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
import ctypes

BASE_DIR = Path(__file__).resolve().parent
LIB_PATH = BASE_DIR / "machine_failure.so"

lib = ctypes.CDLL(str(LIB_PATH))
lib.predict_percent.argtypes = [ctypes.POINTER(ctypes.c_double)]
lib.predict_percent.restype = ctypes.c_double
lib.predict_category.argtypes = [ctypes.POINTER(ctypes.c_double)]
lib.predict_category.restype = ctypes.c_int

class MachineData(BaseModel):
    threshold: float = 0.5
    air_temp: float = 0.0
    process_temp: float = 0.0
    rot_speed: float = 0.0
    torque: float = 0.0
    tool_wear: float = 0.0

class ModelPrediction(BaseModel):
    failure_percent: float = 0.0
    failure_class: int = 0

api = FastAPI()

api.add_middleware(
    CORSMiddleware,
    allow_origins=[
        "http://localhost:5173",
        "http://127.0.0.1:5173",
        "https://predictive-maintenance-snowy.vercel.app"
    ],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

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
        percent = lib.predict_percent(inp)
        if percent < data.threshold:
            return ModelPrediction(failure_percent=percent, failure_class=-1)
        else:
            print("Here")
            category = lib.predict_category(inp)
            return ModelPrediction(failure_percent=percent, failure_class=category)
    except Exception as e:
        raise HTTPException(status_code=400, detail=str(e))
    
