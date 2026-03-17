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
"lineColor": "#000000",
"fontFamily": "Inter, Segoe UI, Arial, sans-serif",
"fontSize": "19px",
"clusterBkg": "#0f172a",
"clusterBorder": "#334155",
"defaultLinkColor": "#000000",
"nodeBorder": "#475569",
"edgeLabelBackground": "#0b1220"
}
}}%%

flowchart TD

%% Entry Points
subgraph ENTRY POINTS["Entry Points"]

subgraph READ_API["Read Api"]

INPUT_TEMP["<div style='text-align:center;font-size:20px;font-weight:700;'>Temperature</div>

<div style='text-align:left'>temperature_entry_point()</div>"]

INPUT_TIME["<div style='text-align:center;font-size:20px;font-weight:700;'>Time</div>

<div style='text-align:left'>time_entry_point()</div>"]

INPUT_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic</div>

<div style='text-align:left'>traffic_entry_point()</div>"]

end

subgraph WRITE_API["Write Api"]

OUTPUT_COOL["<div style='text-align:center;font-size:20px;font-weight:700;'>Cooling</div>

<div style='text-align:left'>city_api_cooling_entry_point()</div>"]

OUTPUT_LIGHT["<div style='text-align:center;font-size:20px;font-weight:700;'>Lighting</div>

<div style='text-align:left'>city_api_lighting_entry_point()"]

OUTPUT_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic</div>

<div style='text-align:left'>city_api_traffic_entry_point()</div>"]

end

end

%% Data sources
subgraph DATASOURCES["Data Sources"]

DS_TEMP["<div style='text-align:center;font-size:20px;font-weight:700;'>Temperature Data Source [S]</div>

<div style='text-align:left'>Forwards raw data</div>"]

DS_TIME["<div style='text-align:center;font-size:20px;font-weight:700;'>Time Data Source [S]</div>

<div style='text-align:left'>Forwards raw data</div>"]

DS_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic Data Source [S]</div>

<div style='text-align:left'>Forwards raw data</div>"]

end

%% Data holders
subgraph DATAHOLDERS["Data Holders"]

DH_TEMP["<div style='text-align:center;font-size:20px;font-weight:700;'>Temperature Data Holder [O + S]</div>

<div style='text-align:left'>Validates & Builds a typed temperature object</div>"]

DH_TIME["<div style='text-align:center;font-size:20px;font-weight:700;'>Time Data Holder [O + S]</div>

<div style='text-align:left'>Validates & Builds a typed time object</div>"]

DH_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic Data Holder [O + S]</div>

<div style='text-align:left'>Validates & Builds a typed traffic object</div>"]

end

%% Events
subgraph EVENTS["Events"]

EV_COOL["<div style='text-align:center;font-size:20px;font-weight:700;'>Cooling Event [O+S]</div>

<div style='text-align:left'>Uses Cooling System Algorithm</div>"]

EV_NIGHT["<div style='text-align:center;font-size:20px;font-weight:700;'>Night Event [O+S]</div>

<div style='text-align:left'>When night falls (18:00-06:59), turn-on streetlights</div>"]

EV_DAY["<div style='text-align:center;font-size:20px;font-weight:700;'>Day Event [O+S]</div>

<div style='text-align:left'>When day arrives (07:00-17:59), turn-off streetlights</div>"]

EV_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic Event [O+S]</div>

<div style='text-align:left'>Uses Traffic Light Algorithm</div>"]

end

%% Aggregators
subgraph AGGREGATORS["Aggregators"]

AGG_LIGHT["<div style='text-align:center;font-size:20px;font-weight:700;'>Lighting Aggregator [O+S]</div>

<div style='text-align:left'>Combines day and night event state into one lighting decision</div>"]

end

%% Response
subgraph Responses["Responses"]

EFF_COOL["<div style='text-align:center;font-size:20px;font-weight:700;'>Cooling System Response [O]</div>

<div style='text-align:left'>Transforms the cooling command into a concrete system action</div>"]

EFF_LIGHT["<div style='text-align:center;font-size:20px;font-size:20px;font-weight:700;'>Lighting System Response [O]</div>

<div style='text-align:left'>Transforms the lighting command into a concrete system action</div>"]

EFF_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic Light Controller Response [O]</div>

<div style='text-align:left'>Transforms the traffic command into a concrete system action</div>"]

end

%% Flow

INPUT_TEMP -- "raw temperature data" --> DS_TEMP
INPUT_TIME -- "raw time data" --> DS_TIME
INPUT_TRAFFIC -- "raw traffic data" --> DS_TRAFFIC

DS_TEMP -- "raw temperature data" --> DH_TEMP
DS_TIME -- "raw time data" --> DH_TIME
DS_TRAFFIC -- "raw traffic data" --> DH_TRAFFIC

DH_TEMP -- "validated temperature object" --> EV_COOL
DH_TIME -- "validated time object" --> EV_NIGHT
DH_TIME -- "validated time object" --> EV_DAY
DH_TRAFFIC -- "validated traffic object" --> EV_TRAFFIC

EV_COOL -- "cooling command" --> EFF_COOL
EV_NIGHT -- "night event { is_ready, time payload }" --> AGG_LIGHT
EV_DAY -- "day event { is_ready, time payload }" --> AGG_LIGHT
EV_TRAFFIC -- "traffic command" --> EFF_TRAFFIC

AGG_LIGHT -- "lighting command" --> EFF_LIGHT

EFF_COOL -- "cooling command" --> OUTPUT_COOL
EFF_LIGHT -- "lighting command" --> OUTPUT_LIGHT
EFF_TRAFFIC -- "traffic command" --> OUTPUT_TRAFFIC

%% Node styles
classDef mainStyle fill:#132033,stroke:#7dd3fc,color:#e6edf3,stroke-width:2px;
classDef entrypointStyle fill:#0f2f2f,stroke:#5eead4,color:#e6fffb,stroke-width:2px;
classDef sourceStyle fill:#142c46,stroke:#93c5fd,color:#eaf2ff,stroke-width:2px;
classDef holderStyle fill:#1f2937,stroke:#94a3b8,color:#f3f4f6,stroke-width:2px;
classDef triggerStyle fill:#3a2a12,stroke:#fbbf24,color:#fff7e6,stroke-width:2px;
classDef aggregatorStyle fill:#2e1f4d,stroke:#c4b5fd,color:#f5f3ff,stroke-width:2px;
classDef responseStyle fill:#163223,stroke:#86efac,color:#ecfdf5,stroke-width:2px;
classDef envStyle fill:#3b1830,stroke:#f9a8d4,color:#fdf2f8,stroke-width:2px;

class INPUT_TEMP,INPUT_TIME,INPUT_TRAFFIC,OUTPUT_COOL,OUTPUT_LIGHT,OUTPUT_TRAFFIC entrypointStyle
class DS_TEMP,DS_TIME,DS_TRAFFIC sourceStyle
class DH_TEMP,DH_TIME,DH_TRAFFIC holderStyle
class EV_COOL,EV_NIGHT,EV_DAY,EV_TRAFFIC triggerStyle
class AGG_COOL,AGG_LIGHT,AGG_TRAFFIC aggregatorStyle
class EFF_COOL,EFF_LIGHT,EFF_TRAFFIC responseStyle

linkStyle default stroke:#000000,stroke-width:2px

```

## Notation

- `[O]` = the component exposes an **Observer**
- `[S]` = the component exposes a **Subject**
- `[O + S]` = the component exposes both an **Observer** and a **Subject** 


## Design Notes

1. **Aggregator Usage**

In some parts of the system, the event could have been sent **directly to the response module** without passing through an aggregator, since there is no actual merging of multiple inputs in those cases.

However, in a project of this size, it is preferable to keep the **aggregator layer in place**.  
Although this introduces a small amount of additional code, it preserves a consistent architecture and allows the system to **scale more easily in the future** if additional inputs or decision logic are introduced.

---

2. **Data Source vs Data Holder**

In this implementation, the **Data Source** and **Data Holder** are separated into different modules.

Technically, they could have been combined into a single component.

We prefer to keep this design modular for cases where the stored information needs to maintain its own state.

In this design:

- **Data Source** is responsible for publishing and propagating information
- **Data Holder** is responsible for storing the latest state

---

3. **Aggregator "busy wait loop"**

The **Aggregator** is responsible for syncing several upstream observers before propagating the final decision to the next stage.

Aggregator must ensure that **all required inputs have completed their computation** before publishing the result.

Each upstream observer updates its own `is_ready` flag when it finishes processing.  
The Aggregator checks the state of all its dependent observers and only proceeds when **all of them are ready at the same time**.

If this condition is not satisfied, the Aggregator simply **exits the current flow** and waits for the next incoming event. When a new event arrives, the Aggregator checks the observers again to determine whether all required inputs are ready.

Because the **subjects associated with the Aggregator are global objects**, their state is accessible whenever a new event reaches the Aggregator, allowing it to evaluate whether the full set of inputs is ready.
