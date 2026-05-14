import { METRICS, NORMAL_MACHINE } from "../data/simulationConfig"

const randomBetween = (min, max) => Math.random() * (max - min) + min

const clamp = (value, min, max) => Math.min(Math.max(value, min), max)

const metricRange = (key) => METRICS.find((metric) => metric.key === key)

const clampMachine = (machine) =>
  Object.fromEntries(
    Object.entries(machine).map(([key, value]) => {
      const metric = metricRange(key)
      return [key, metric ? clamp(value, metric.min, metric.max) : value]
    }),
  )

const actionDelta = {
  boost_temp: {
    air_temp: 0.24,
    process_temp: 0.34,
    rot_speed: -3.5,
    torque: 0.05,
    tool_wear: 0.05,
  },
  increase_load: {
    air_temp: 0.04,
    process_temp: 0.2,
    rot_speed: -7,
    torque: 0.28,
    tool_wear: 0.11,
  },
  boost_speed: {
    air_temp: 0.02,
    process_temp: 0.12,
    rot_speed: 16,
    torque: -0.04,
    tool_wear: 0.06,
  },
  wear_tool: {
    air_temp: 0.01,
    process_temp: 0.08,
    rot_speed: -2,
    torque: 0.1,
    tool_wear: 0.72,
  },
  cool_machine: {
    air_temp: -0.28,
    process_temp: -0.42,
    rot_speed: 1.5,
    torque: -0.03,
    tool_wear: 0,
  },
}

export const createActionEvent = (type) => ({
  id: `${type}-${Date.now()}-${Math.random()}`,
  type,
  remaining: type === "stabilize" ? 20 : 14,
  duration: type === "stabilize" ? 20 : 14,
})

export const nextMachineState = (machine, mode, actionEvents) => {
  let next = { ...machine }

  Object.keys(machine).forEach((key) => {
    const target = mode.target[key]
    const noise = randomBetween(-mode.noise, mode.noise)

    if (key === "rot_speed") {
      next[key] += (target - machine[key]) * 0.045 + noise * 9
    } else if (key === "tool_wear") {
      next[key] += Math.max((target - machine[key]) * 0.012, 0) + randomBetween(0.02, 0.16)
    } else {
      next[key] += (target - machine[key]) * 0.05 + noise * 0.08
    }
  })

  actionEvents.forEach((event) => {
    const strength = event.remaining / event.duration

    if (event.type === "stabilize") {
      Object.keys(next).forEach((key) => {
        next[key] += (NORMAL_MACHINE[key] - next[key]) * 0.08 * strength
      })
      return
    }

    const delta = actionDelta[event.type]
    Object.keys(delta).forEach((key) => {
      next[key] += delta[key] * strength
    })
  })

  if (mode.id === "unstable") {
    next.rot_speed += randomBetween(-28, 28)
    next.torque += randomBetween(-1.1, 1.1)
    next.process_temp += randomBetween(-0.18, 0.22)
  }

  return clampMachine(next)
}

export const decayActionEvents = (actionEvents) =>
  actionEvents
    .map((event) => ({ ...event, remaining: event.remaining - 1 }))
    .filter((event) => event.remaining > 0)

export const normalizePercent = (value) => {
  if (!Number.isFinite(value)) {
    return 0
  }

  const percent = value * 100
  return clamp(percent, 0, 100)
}

export const formatMetric = (value, digits) => Number(value).toFixed(digits)
