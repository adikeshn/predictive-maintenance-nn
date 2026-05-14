import { AlertTriangle, CheckCircle2, RadioTower } from "lucide-react"
import { FAILURE_LABELS } from "../data/simulationConfig"

function PredictionPanel({ prediction, isRunning, apiError, isFetching, threshold }) {
  const risk = prediction.failurePercent
  const isHighRisk = risk >= threshold
  const failureLabel =
    prediction.failureClass === null ? "Waiting for threshold" : FAILURE_LABELS[prediction.failureClass] ?? `Class ${prediction.failureClass}`

  return (
    <section className={`panel prediction ${isHighRisk ? "prediction--risk" : ""}`}>
      <div className="panel__title">
        <div>
          <p>Live Model Output</p>
          <h2>{isHighRisk ? "Failure likely" : "System stable"}</h2>
        </div>
        {isHighRisk ? <AlertTriangle size={23} /> : <CheckCircle2 size={23} />}
      </div>

      <div className="risk-display">
        <span>Failure Risk</span>
        <strong>{risk.toFixed(1)}%</strong>
        <div className="risk-meter" aria-hidden="true">
          <div style={{ width: `${risk}%` }} />
        </div>
      </div>

      <div className="prediction-details">
        {isHighRisk ? (
          <>
            <span>Predicted Type</span>
            <strong>{failureLabel}</strong>
          </>
        ) : (
          <>
            <span>Status</span>
            <strong>Machine operating normally</strong>
          </>
        )}
      </div>

      <div className="api-status">
        <RadioTower size={16} />
        {apiError ? (
          <span className="api-status__error">{apiError}</span>
        ) : isFetching ? (
          <span>Fetching model output...</span>
        ) : isRunning ? (
          <span>Auto-fetching every few seconds</span>
        ) : (
          <span>Simulation paused</span>
        )}
      </div>
    </section>
  )
}

export default PredictionPanel
