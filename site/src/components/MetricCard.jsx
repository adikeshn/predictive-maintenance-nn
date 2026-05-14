import { Activity } from "lucide-react"
import { formatMetric } from "../utils/simulation"

function MetricCard({ metric, value }) {
  const position = ((value - metric.min) / (metric.max - metric.min)) * 100

  return (
    <article className="metric-card">
      <div className="metric-card__top">
        <span>{metric.label}</span>
        <Activity size={17} />
      </div>

      <strong>
        {formatMetric(value, metric.digits)}
        <span>{metric.unit}</span>
      </strong>

      <div className="metric-card__bar" aria-hidden="true">
        <div style={{ width: `${Math.min(Math.max(position, 0), 100)}%` }} />
      </div>
    </article>
  )
}

export default MetricCard
