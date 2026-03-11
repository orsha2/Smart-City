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
"fontSize": "15px",
"clusterBkg": "#0f172a",
"clusterBorder": "#334155",
"defaultLinkColor": "#000000",
"nodeBorder": "#475569"
}
}}%%

flowchart TD

%% Hooks
subgraph HOOKS["Hooks"]

subgraph READ_HOOKS["Read Hooks"]

INPUT_TEMP["<div style='text-align:center;font-size:20px;font-weight:700;'>Temperature</div>

<div style='text-align:left'> read_temperature_sensor() </div>"]

INPUT_TIME["<div style='text-align:center;font-size:20px;font-weight:700;'>Time</div>

<div style='text-align:left'> read_time_sensor() </div>"]

INPUT_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic</div>

<div style='text-align:left'> read_traffic_sensor() </div>"]

end

subgraph WRITE_HOOKS["Write Hooks"]

OUTPUT_COOL["<div style='text-align:center;font-size:20px;font-weight:700;'>Cooling</div>

<div style='text-align:left'> activate_cooling() </div>"]

OUTPUT_LIGHT["<div style='text-align:center;font-size:20px;font-weight:700;'>Lighting</div>

<div style='text-align:left'> turn_streetlights_on_off() </div>"]

OUTPUT_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic</div>

<div style='text-align:left'> adjust_traffic_light_timing() </div>"]

end

end

%% Data sources
subgraph DATASOURCES["Data Sources"]

DS_TEMP["<div style='text-align:center;font-size:20px;font-weight:700;'>Temperature Data Source [S]</div>

<div style='text-align:left'> Reads temperature input<br/> Publishes a temperature event </div>"]

DS_TIME["<div style='text-align:center;font-size:20px;font-weight:700;'>Time Data Source [S]</div>

<div style='text-align:left'> Reads current hour<br/> Publishes a time event </div>"]

DS_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic Data Source [S]</div>

<div style='text-align:left'> Reads congestion level<br/> Publishes a traffic event </div>"]

end

%% Data holders
subgraph DATAHOLDERS["Data Holders"]

DH_TEMP["<div style='text-align:center;font-size:20px;font-weight:700;'>Temperature Data Holder [O + S]</div>

<div style='text-align:left'> Stores latest temperature<br/> Unit: °C </div>"]

DH_TIME["<div style='text-align:center;font-size:20px;font-weight:700;'>Time Data Holder [O + S]</div>

<div style='text-align:left'> Stores latest hour<br/> Range: 0-23 </div>"]

DH_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic Data Holder [O + S]</div>

<div style='text-align:left'> Stores latest congestion<br/> Range: 0-100% </div>"]

end

%% Triggers
subgraph TRIGGERS["Triggers"]

TRIG_COOL["<div style='text-align:center;font-size:20px;font-weight:700;'>Cooling Trigger [O+S]</div>

<div style='text-align:left'> Evaluates cooling condition<br/> Uses cooling algorithm </div>"]

TRIG_NIGHT["<div style='text-align:center;font-size:20px;font-weight:700;'>Night Trigger [O+S]</div>

<div style='text-align:left'> Active between<br/> 18:00 and 06:59 </div>"]

TRIG_DAY["<div style='text-align:center;font-size:20px;font-weight:700;'>Day Trigger [O+S]</div>

<div style='text-align:left'> Active between<br/> 07:00 and 17:59 </div>"]

TRIG_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic Trigger [O+S]</div>

<div style='text-align:left'> Evaluates congestion condition<br/> Uses traffic algorithm </div>"]

end

%% Aggregators
subgraph AGGREGATORS["Aggregators"]

AGG_COOL["<div style='text-align:center;font-size:20px;font-weight:700;'>Cooling Aggregator [O+S]</div>

<div style='text-align:left'> Collects trigger results<br/> Produces cooling decision </div>"]

AGG_LIGHT["<div style='text-align:center;font-size:20px;font-weight:700;'>Lighting Aggregator [O+S]</div>

<div style='text-align:left'> Combines day and night state<br/> Produces lighting decision </div>"]

AGG_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic Aggregator [O+S]</div>

<div style='text-align:left'> Collects traffic trigger results<br/> Produces traffic policy </div>"]

end

%% Effects
subgraph EFFECTS["Effects"]

EFF_COOL["<div style='text-align:center;font-size:20px;font-weight:700;'>Cooling System Effect [O]</div>

<div style='text-align:left'> Activates or deactivates cooling </div>"]

EFF_LIGHT["<div style='text-align:center;font-size:20px;font-weight:700;'>Lighting System Effect [O]</div>

<div style='text-align:left'> Turns streetlights on or off </div>"]

EFF_TRAFFIC["<div style='text-align:center;font-size:20px;font-weight:700;'>Traffic Light Controller Effect [O]</div>

<div style='text-align:left'> Adjusts traffic light timing </div>"]

end

%% Flow

INPUT_TEMP --> DS_TEMP
INPUT_TIME --> DS_TIME
INPUT_TRAFFIC --> DS_TRAFFIC

DS_TEMP --> DH_TEMP
DS_TIME --> DH_TIME
DS_TRAFFIC --> DH_TRAFFIC

DH_TEMP --> TRIG_COOL
DH_TIME --> TRIG_NIGHT
DH_TIME --> TRIG_DAY
DH_TRAFFIC --> TRIG_TRAFFIC

TRIG_COOL --> AGG_COOL
TRIG_NIGHT --> AGG_LIGHT
TRIG_DAY --> AGG_LIGHT
TRIG_TRAFFIC --> AGG_TRAFFIC

AGG_COOL --> EFF_COOL
AGG_LIGHT --> EFF_LIGHT
AGG_TRAFFIC --> EFF_TRAFFIC

EFF_COOL --> OUTPUT_COOL
EFF_LIGHT --> OUTPUT_LIGHT
EFF_TRAFFIC --> OUTPUT_TRAFFIC

%% Node styles
classDef mainStyle fill:#132033,stroke:#7dd3fc,color:#e6edf3,stroke-width:2px;
classDef hooksStyle fill:#0f2f2f,stroke:#5eead4,color:#e6fffb,stroke-width:2px;
classDef sourceStyle fill:#142c46,stroke:#93c5fd,color:#eaf2ff,stroke-width:2px;
classDef holderStyle fill:#1f2937,stroke:#94a3b8,color:#f3f4f6,stroke-width:2px;
classDef triggerStyle fill:#3a2a12,stroke:#fbbf24,color:#fff7e6,stroke-width:2px;
classDef aggregatorStyle fill:#2e1f4d,stroke:#c4b5fd,color:#f5f3ff,stroke-width:2px;
classDef effectStyle fill:#163223,stroke:#86efac,color:#ecfdf5,stroke-width:2px;
classDef envStyle fill:#3b1830,stroke:#f9a8d4,color:#fdf2f8,stroke-width:2px;

class MAIN mainStyle
class INPUT_TEMP,INPUT_TIME,INPUT_TRAFFIC,OUTPUT_COOL,OUTPUT_LIGHT,OUTPUT_TRAFFIC hooksStyle
class DS_TEMP,DS_TIME,DS_TRAFFIC sourceStyle
class DH_TEMP,DH_TIME,DH_TRAFFIC holderStyle
class TRIG_COOL,TRIG_NIGHT,TRIG_DAY,TRIG_TRAFFIC triggerStyle
class AGG_COOL,AGG_LIGHT,AGG_TRAFFIC aggregatorStyle
class EFF_COOL,EFF_LIGHT,EFF_TRAFFIC effectStyle
class CITY envStyle

linkStyle default stroke:#000000,stroke-width:2px