import { useEffect, useMemo, useRef, useState } from "react";
import { Cpu, LineChart as LineChartIcon } from "lucide-react";
import "./App.css";
import ControlPanel from "./components/ControlPanel";
import LiveLineChart from "./components/LiveLineChart";
import MetricCard from "./components/MetricCard";
import PredictionPanel from "./components/PredictionPanel";
import {
  API_URL,
  HISTORY_LIMIT,
  METRICS,
  MODES,
  NORMAL_MACHINE,
  PREDICTION_INTERVAL_MS,
  SIMULATION_INTERVAL_MS,
} from "./data/simulationConfig";
import {
  createActionEvent,
  decayActionEvents,
  nextMachineState,
  normalizePercent,
} from "./utils/simulation";

const createHistoryPoint = (time, machine, failurePercent = 0) => ({
  time,
  ...machine,
  failurePercent,
});

function App() {
  const [machine, setMachine] = useState(NORMAL_MACHINE);
  const [history, setHistory] = useState([
    createHistoryPoint(0, NORMAL_MACHINE),
  ]);
  const [selectedMode, setSelectedMode] = useState(MODES[0]);
  const [isRunning, setIsRunning] = useState(false);
  const [actionEvents, setActionEvents] = useState([]);
  const [threshold, setThreshold] = useState(50);
  const [prediction, setPrediction] = useState({
    failurePercent: 0,
    failureClass: null,
  });
  const [isFetching, setIsFetching] = useState(false);
  const [apiError, setApiError] = useState("");

  const timeRef = useRef(0);
  const machineRef = useRef(machine);
  const thresholdRef = useRef(threshold);

  useEffect(() => {
    machineRef.current = machine;
  }, [machine]);

  useEffect(() => {
    thresholdRef.current = threshold;
  }, [threshold]);

  useEffect(() => {
    if (!isRunning) {
      return undefined;
    }

    const intervalId = window.setInterval(() => {
      setMachine((current) => {
        const next = nextMachineState(current, selectedMode, actionEvents);
        machineRef.current = next;
        timeRef.current += 1;

        setHistory((oldHistory) => [
          ...oldHistory.slice(-(HISTORY_LIMIT - 1)),
          createHistoryPoint(timeRef.current, next, prediction.failurePercent),
        ]);

        return next;
      });

      setActionEvents((current) => decayActionEvents(current));
    }, SIMULATION_INTERVAL_MS);

    return () => window.clearInterval(intervalId);
  }, [actionEvents, isRunning, prediction.failurePercent, selectedMode]);

  useEffect(() => {
    if (!isRunning) {
      return undefined;
    }
    const fetchPrediction = async () => {
      setIsFetching(true);
      setApiError("");

      try {
        const basePayload = {
          ...machineRef.current,
          threshold: threshold / 100,
        };
        const percentResponse = await fetch(API_URL, {
          method: "POST",
          headers: { "Content-Type": "application/json" },
          body: JSON.stringify(basePayload),
        });
        if (!percentResponse.ok) {
          throw new Error("Could not fetch failure risk");
        }

        const percentData = await percentResponse.json();
        const failurePercent = normalizePercent(percentData.failure_percent);
        let failureClass = null;

        if (percentData.failure_class != -1) {
          failureClass = percentData.failure_class;
        }

        setPrediction({ failurePercent, failureClass });

        setHistory((oldHistory) => {
          if (oldHistory.length === 0) {
            return oldHistory;
          }

          const updated = [...oldHistory];
          updated[updated.length - 1] = {
            ...updated[updated.length - 1],
            failurePercent,
          };
          return updated;
        });
      } catch (error) {
        setApiError(error.message || "Could not connect to API");
      } finally {
        setIsFetching(false);
      }
    };

    fetchPrediction();
    const intervalId = window.setInterval(
      fetchPrediction,
      PREDICTION_INTERVAL_MS,
    );

    return () => window.clearInterval(intervalId);
  }, [isRunning]);

  const currentModeDescription = useMemo(
    () => `${selectedMode.label}: ${selectedMode.description}`,
    [selectedMode],
  );

  const handleReset = () => {
    timeRef.current = 0;
    setMachine(NORMAL_MACHINE);
    setHistory([createHistoryPoint(0, NORMAL_MACHINE)]);
    setPrediction({ failurePercent: 0, failureClass: null });
    setActionEvents([]);
    setApiError("");
    setSelectedMode(MODES[0]);
    setIsRunning(false);
  };

  const addAction = (actionId) => {
    setActionEvents((current) => [...current, createActionEvent(actionId)]);
  };

  return (
    <main className="app-shell">
      <header className="hero">
        <div>
          <div className="eyebrow">
            <Cpu size={18} />C Neural Network + FastAPI
          </div>
          <h1>Predictive Maintenance Simulator</h1>
          <p>
            Simulate machine conditions, stream the inputs as live graphs, and
            auto-fetch the model output while the system runs. Failure risk
            prediction implemented using a neural net built from scratch in C.
          </p>
        </div>

        <div className={`run-pill ${isRunning ? "run-pill--on" : ""}`}>
          <span />
          {isRunning ? "Simulation Running" : "Simulation Paused"}
        </div>
      </header>

      <section className="layout">
        <ControlPanel
          isRunning={isRunning}
          selectedMode={selectedMode}
          actionEvents={actionEvents}
          threshold={threshold}
          onToggleRunning={() => setIsRunning((current) => !current)}
          onReset={handleReset}
          onModeChange={setSelectedMode}
          onAction={addAction}
          onThresholdChange={setThreshold}
        />

        <section className="main-column">
          <section className="metric-grid">
            {METRICS.map((metric) => (
              <MetricCard
                key={metric.key}
                metric={metric}
                value={machine[metric.key]}
              />
            ))}
          </section>

          <PredictionPanel
            prediction={prediction}
            isRunning={isRunning}
            apiError={apiError}
            isFetching={isFetching}
            threshold={threshold}
          />

          <section className="panel graph-panel">
            <div className="panel__title">
              <div>
                <p>Current Mode</p>
                <h2>{currentModeDescription}</h2>
              </div>
              <LineChartIcon size={23} />
            </div>

            <div className="charts-grid">
              {METRICS.map((metric) => (
                <LiveLineChart
                  key={metric.key}
                  title={metric.label}
                  data={history}
                  dataKey={metric.key}
                  unit={metric.unit}
                  domain={[metric.min, metric.max]}
                  digits={metric.digits}
                />
              ))}

              <LiveLineChart
                title="Failure Risk"
                data={history}
                dataKey="failurePercent"
                unit="%"
                domain={[0, 100]}
                digits={1}
              />
            </div>
          </section>
        </section>
      </section>
    </main>
  );
}

export default App;
