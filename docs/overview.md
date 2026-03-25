```mermaid

%%{init: {
"theme": "base",
"flowchart": {
"htmlLabels": true,
"curve": "linear"
},
"themeVariables": {
"background": "#0b1220",
"primaryTextColor": "#e6edf3",
"secondaryTextColor": "#cbd5e1",
"tertiaryTextColor": "#94a3b8",
"lineColor": "#64748b",
"fontFamily": "Inter, Segoe UI, Arial, sans-serif",
"fontSize": "19px",
"clusterBkg": "#0f172a",
"clusterBorder": "#334155",
"defaultLinkColor": "#64748b",
"nodeBorder": "#475569",
"edgeLabelBackground": "#0b1220"
}
}}%%
flowchart TD

%% Read API
subgraph READ_API["Read API · Inputs"]

INPUT_TEMPERATURE["<div style='text-align:center;font-size:20px;font-weight:700;'>Temperature</div>
<div style='text-align:left'>temperature_entry_point()</div>"]

INPUT_TIME["<div style='text-align:center;font-size:20px;font-weight:700;'>Time</div>
<div style='text-align:left'>time_entry_point()</div>"]

INPUT_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic</div>
<div style='text-align:left'>traffic_entry_point()</div>"]

end

%% Data Sources
subgraph DATASOURCES["Data Sources"]

DS_TEMPERATURE["<div style='text-align:center;font-size:20px;font-weight:700;'>Temperature Data Source</div>
<div style='text-align:left'>Reads raw temperature from HAL and publishes downstream</div>"]

DS_TIME["<div style='text-align:center;font-size:20px;font-weight:700;'>Time Data Source</div>
<div style='text-align:left'>Reads raw time from HAL and publishes downstream</div>"]

DS_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic Data Source</div>
<div style='text-align:left'>Reads raw traffic data from HAL and publishes downstream</div>"]

end

%% Data Holders
subgraph DATAHOLDERS["Data Holders"]

DH_TEMPERATURE_A["<div style='text-align:center;font-size:20px;font-weight:700;'>Temperature Data Holder - Area A</div>
<div style='text-align:left'>Validates and stores Area A temperature</div>"]

DH_TEMPERATURE_B["<div style='text-align:center;font-size:20px;font-weight:700;'>Temperature Data Holder - Area B</div>
<div style='text-align:left'>Validates and stores Area B temperature</div>"]

DH_TEMPERATURE_C["<div style='text-align:center;font-size:20px;font-weight:700;'>Temperature Data Holder - Area C</div>
<div style='text-align:left'>Validates and stores Area C temperature</div>"]

DH_TIME["<div style='text-align:center;font-size:20px;font-weight:700;'>Time Data Holder</div>
<div style='text-align:left'>Validates and stores structured time data</div>"]

DH_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic Data Holder</div>
<div style='text-align:left'>Validates and stores structured traffic data</div>"]

end

%% Aggregators
subgraph AGGREGATORS["Aggregators"]

AGG_TEMPERATURE["<div style='text-align:center;font-size:20px;font-weight:700;'>Temperature Aggregator</div>
<div style='text-align:left'>Holds list of 3 area states (A, B, C)</div>
<div style='text-align:left'>≥ 2 areas above high threshold → cooling on</div>
<div style='text-align:left'>≥ 2 areas below low threshold → cooling off</div>
<div style='text-align:left'>Otherwise → hold current state</div>"]

end

%% Events
subgraph EVENTS["Events"]

EV_LIGHT["<div style='text-align:center;font-size:20px;font-weight:700;'>Lighting Event</div>
<div style='text-align:left'>Publishes only on lighting state change</div>
<div style='text-align:left'>18:00 → lights on · 07:00 → lights off</div>"]

EV_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic Event</div>
<div style='text-align:left'>Applies the traffic light algorithm</div>"]

end

%% Responses
subgraph RESPONSES["Responses"]

RESP_COOL["<div style='text-align:center;font-size:20px;font-weight:700;'>Cooling Response</div>
<div style='text-align:left'>Executes the cooling decision via Write API</div>"]

RESP_LIGHT["<div style='text-align:center;font-size:20px;font-weight:700;'>Lighting Response</div>
<div style='text-align:left'>Executes the lighting command via Write API</div>"]

RESP_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic Light Controller Response</div>
<div style='text-align:left'>Executes the traffic command via Write API</div>"]

end

%% Write API
subgraph WRITE_API["Write API · Outputs"]

OUTPUT_COOL["<div style='text-align:center;font-size:20px;font-weight:700;'>Cooling</div>
<div style='text-align:left'>city_api_cooling_entry_point()</div>"]

OUTPUT_LIGHT["<div style='text-align:center;font-size:20px;font-weight:700;'>Lighting</div>
<div style='text-align:left'>city_api_lighting_entry_point()</div>"]

OUTPUT_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic</div>
<div style='text-align:left'>city_api_traffic_entry_point()</div>"]

end

%% Flow
INPUT_TEMPERATURE -- "runtime signal" -->DS_TEMPERATURE
INPUT_TIME -- "runtime signal" -->DS_TIME
INPUT_TRAFFIC -- "runtime signal" -->DS_TRAFFIC

DS_TEMPERATURE -- "raw temperature" --> DH_TEMPERATURE_A
DS_TEMPERATURE -- "raw temperature" --> DH_TEMPERATURE_B
DS_TEMPERATURE -- "raw temperature" --> DH_TEMPERATURE_C

DS_TIME -- "raw time" --> DH_TIME
DS_TRAFFIC -- "raw traffic" --> DH_TRAFFIC

DH_TEMPERATURE_A -- "Area A temperature" --> AGG_TEMPERATURE
DH_TEMPERATURE_B -- "Area B temperature" --> AGG_TEMPERATURE
DH_TEMPERATURE_C -- "Area C temperature" --> AGG_TEMPERATURE

DH_TIME -- "validated time" --> EV_LIGHT
DH_TRAFFIC -- "validated traffic" --> EV_TRAFFIC

AGG_TEMPERATURE -- "cooling command" --> RESP_COOL
EV_LIGHT -- "lighting command" --> RESP_LIGHT
EV_TRAFFIC -- "traffic command" --> RESP_TRAFFIC

RESP_COOL -- "cooling command" --> OUTPUT_COOL
RESP_LIGHT -- "lighting command" --> OUTPUT_LIGHT
RESP_TRAFFIC -- "traffic command" --> OUTPUT_TRAFFIC

%% Styles
classDef readApiStyle fill:#0f2f2f,stroke:#5eead4,color:#e6fffb,stroke-width:2px;
classDef writeApiStyle fill:#2a1f0f,stroke:#fbbf24,color:#fff7e6,stroke-width:2px;
classDef sourceStyle fill:#142c46,stroke:#93c5fd,color:#eaf2ff,stroke-width:2px;
classDef holderStyle fill:#1f2937,stroke:#94a3b8,color:#f3f4f6,stroke-width:2px;
classDef aggregatorStyle fill:#2e1f4d,stroke:#c4b5fd,color:#f5f3ff,stroke-width:2px;
classDef eventStyle fill:#3a2a12,stroke:#fbbf24,color:#fff7e6,stroke-width:2px;
classDef responseStyle fill:#163223,stroke:#86efac,color:#ecfdf5,stroke-width:2px;

class INPUT_TEMPERATURE,INPUT_TIME,INPUT_TRAFFIC readApiStyle
class OUTPUT_COOL,OUTPUT_LIGHT,OUTPUT_TRAFFIC writeApiStyle
class DS_TEMPERATURE,DS_TIME,DS_TRAFFIC sourceStyle
class DH_TEMPERATURE_A,DH_TEMPERATURE_B,DH_TEMPERATURE_C,DH_TIME,DH_TRAFFIC holderStyle
class AGG_TEMPERATURE aggregatorStyle
class EV_LIGHT,EV_TRAFFIC eventStyle
class RESP_COOL,RESP_LIGHT,RESP_TRAFFIC responseStyle

linkStyle default stroke:#64748b,stroke-width:2px

```

## Notation

Each component implements the Observer pattern:

| Component | Observer Pattern Role |
|-----------|----------------------|
| Read API | Trigger only - carries no data |
| Data Source | `[S]` Subject - reads from HAL, publishes raw data |
| Data Holder | `[O + S]` Observer + Subject - validates and republishes |
| Aggregator | `[O + S]` Observer + Subject - synchronizes multiple inputs |
| Event | `[O + S]` Observer + Subject - applies business logic |
| Response | `[O]` Observer - final consumer, no downstream propagation |
| Write API | Final boundary - actuates external systems |


## Design Notes

1. **Entry Points** - Forwards a runtime signal to downstream modules. Carries no data; does not read HAL.

2. **Data Sources** - Reads raw data from HAL and publishes downstream. Typically no validation.

3. **Data Holders** - Validates, parses, and stores raw data, then publishes downstream. The Temperature pipeline has 3 Data Holders (Area A, B, C).

4. **Temperature Aggregator** - Receives validated readings from Areas A, B, and C. Holds a list of 3 area states. Cooling decision:
   - ≥ 2 areas above high threshold → cooling on
   - ≥ 2 areas below low threshold → cooling off
   - otherwise → hold current state

   Publishes the cooling command directly to the Response. No Event stage.

5. **Aggregator synchronization** - Each upstream observer sets `is_ready` on completion. The Aggregator checks all flags before publishing; if any are unset, it exits and waits for the next event. After publishing, all `is_ready` flags are reset. Upstream subjects are global, so if a sensor was absent in a cycle its last value persists, bounded to at most one cycle old.

6. **Lighting Event** - Checks validated time and publishes only on state change:
   - 18:00 → lights on (transition from off)
   - 07:00 → lights off (transition from on)
   - No publish if the lighting state has not changed.

7. **Traffic Event** - Applies the traffic light algorithm and publishes the resulting command.
