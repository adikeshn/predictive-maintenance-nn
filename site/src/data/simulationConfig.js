export const API_URL = import.meta.env.VITE_API_URL ?? "http://127.0.0.1:8000/predict"
export const HISTORY_LIMIT = 50
export const SIMULATION_INTERVAL_MS = 249
export const PREDICTION_INTERVAL_MS = 1200

export const NORMAL_MACHINE = {
  air_temp: 299.2,
  process_temp: 309.1,
  rot_speed: 1500,
  torque: 40,
  tool_wear: 60,
}

export const METRICS = [
  {
    key: "air_temp",
    label: "Air Temp",
    unit: "K",
    min: 295,
    max: 305,
    digits: 1,
  },
  {
    key: "process_temp",
    label: "Process Temp",
    unit: "K",
    min: 305,
    max: 315,
    digits: 1,
  },
  {
    key: "rot_speed",
    label: "Rotation Speed",
    unit: "rpm",
    min: 1150,
    max: 2900,
    digits: 0,
  },
  {
    key: "torque",
    label: "Torque",
    unit: "Nm",
    min: 5,
    max: 80,
    digits: 1,
  },
  {
    key: "tool_wear",
    label: "Tool Wear",
    unit: "min",
    min: 0,
    max: 255,
    digits: 0,
  },
]

export const MODES = [
  {
    id: "normal",
    label: "Normal",
    description: "Stable baseline drift.",
    target: NORMAL_MACHINE,
    noise: 0.55,
  },
  {
    id: "heat",
    label: "High Heat",
    description: "Temperatures slowly climb.",
    target: {
      air_temp: 303.6,
      process_temp: 313.6,
      rot_speed: 1460,
      torque: 44,
      tool_wear: 90,
    },
    noise: 0.75,
  },
  {
    id: "load",
    label: "High Load",
    description: "Torque rises and speed dips.",
    target: {
      air_temp: 301.1,
      process_temp: 311.8,
      rot_speed: 1330,
      torque: 62,
      tool_wear: 125,
    },
    noise: 0.85,
  },
  {
    id: "worn",
    label: "Worn Tool",
    description: "Wear accumulates quickly.",
    target: {
      air_temp: 300.4,
      process_temp: 310.5,
      rot_speed: 1430,
      torque: 50,
      tool_wear: 220,
    },
    noise: 0.65,
  },
  {
    id: "unstable",
    label: "Unstable",
    description: "More aggressive fluctuations.",
    target: {
      air_temp: 302.2,
      process_temp: 312.3,
      rot_speed: 1515,
      torque: 55,
      tool_wear: 145,
    },
    noise: 1.35,
  },
]

export const ACTIONS = [
  {
    id: "boost_temp",
    label: "Boost Temp",
    description: "Raises both temperature readings.",
  },
  {
    id: "increase_load",
    label: "Increase Load",
    description: "Raises torque, heat, and wear.",
  },
  {
    id: "boost_speed",
    label: "Boost Speed",
    description: "Raises rpm while adding heat.",
  },
  {
    id: "wear_tool",
    label: "Wear Tool",
    description: "Accelerates tool wear.",
  },
  {
    id: "cool_machine",
    label: "Cool Machine",
    description: "Pulls temperatures down.",
  },
  {
    id: "stabilize",
    label: "Stabilize",
    description: "Moves values toward normal.",
  },
]

export const FAILURE_LABELS = {
  0: "No Failure",
  1: "Heat Dissipation Failure",
  2: "Power Failure",
  3: "Overstrain Failure",
  4: "Tool Wear Failure",
  5: "Random Failure",
}
