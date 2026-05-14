import { Gauge, Pause, Play, RotateCcw, Zap } from "lucide-react"
import { ACTIONS, MODES } from "../data/simulationConfig"

function ControlPanel({
  isRunning,
  selectedMode,
  actionEvents,
  threshold,
  onToggleRunning,
  onReset,
  onModeChange,
  onAction,
  onThresholdChange,
}) {
  return (
    <aside className="panel controls">
      <div className="panel__title">
        <div>
          <p>Simulation Controls</p>
          <h2>Machine behavior</h2>
        </div>
        <Gauge size={22} />
      </div>

      <div className="primary-controls">
        <button className="btn btn--primary" onClick={onToggleRunning}>
          {isRunning ? <Pause size={18} /> : <Play size={18} />}
          {isRunning ? "Pause" : "Start"}
        </button>
        <button className="btn" onClick={onReset}>
          <RotateCcw size={18} />
          Reset
        </button>
      </div>

      <div className="control-group">
        <label>Failure type threshold</label>
        <div className="threshold-row">
          <input
            min="1"
            max="99"
            type="range"
            value={threshold}
            onChange={(event) => onThresholdChange(Number(event.target.value))}
          />
          <strong>{threshold}%</strong>
        </div>
      </div>

      <div className="control-group">
        <label>Preset mode</label>
        <div className="mode-grid">
          {MODES.map((mode) => (
            <button
              className={`mode-button ${selectedMode.id === mode.id ? "is-active" : ""}`}
              key={mode.id}
              onClick={() => onModeChange(mode)}
            >
              <strong>{mode.label}</strong>
              <span>{mode.description}</span>
            </button>
          ))}
        </div>
      </div>

      <div className="control-group">
        <label>During-simulation actions</label>
        <div className="action-grid">
          {ACTIONS.map((action) => (
            <button
              className="action-button"
              key={action.id}
              onClick={() => onAction(action.id)}
              disabled={!isRunning}
              title={!isRunning ? "Start the simulation first" : action.description}
            >
              <Zap size={15} />
              <span>{action.label}</span>
            </button>
          ))}
        </div>
      </div>

      <div className="active-effects">
        <span>Active effects</span>
        <strong>{actionEvents.length === 0 ? "None" : actionEvents.length}</strong>
      </div>
    </aside>
  )
}

export default ControlPanel
