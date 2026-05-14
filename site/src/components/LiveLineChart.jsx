import {
  LineChart,
  Line,
  XAxis,
  YAxis,
  Tooltip,
  ResponsiveContainer,
  CartesianGrid,
} from "recharts"

function LiveLineChart({ title, data, dataKey, unit, domain, digits = 1 }) {
  return (
    <section className="chart-card">
      <div className="chart-card__header">
        <h3>{title}</h3>
        <span>{unit}</span>
      </div>

      <div className="chart-card__body">
        <ResponsiveContainer width="100%" height="100%">
          <LineChart data={data} margin={{ top: 8, right: 14, bottom: 0, left: -18 }}>
            <CartesianGrid stroke="rgba(148, 163, 184, 0.14)" vertical={false} />
            <XAxis
              dataKey="time"
              tick={{ fill: "#94a3b8", fontSize: 11 }}
              tickLine={false}
              axisLine={false}
              minTickGap={26}
            />
            <YAxis
              domain={domain}
              tick={{ fill: "#94a3b8", fontSize: 11 }}
              tickLine={false}
              axisLine={false}
              width={48}
            />
            <Tooltip
              contentStyle={{
                background: "#0f172a",
                border: "1px solid rgba(148, 163, 184, 0.22)",
                borderRadius: "14px",
                color: "#e5e7eb",
              }}
              labelStyle={{ color: "#cbd5e1" }}
              formatter={(value) => [`${Number(value).toFixed(digits)} ${unit}`, title]}
            />
            <Line
              type="monotone"
              dataKey={dataKey}
              stroke="#38bdf8"
              strokeWidth={2.4}
              dot={false}
              isAnimationActive={false}
            />
          </LineChart>
        </ResponsiveContainer>
      </div>
    </section>
  )
}

export default LiveLineChart
