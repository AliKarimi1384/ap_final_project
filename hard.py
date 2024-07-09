import pandas as pd
import plotly.graph_objs as go

df = pd.read_csv('game_data.csv')

df['Time Stamp'] = pd.to_datetime(df['Time Stamp'])

hard_data = df[df['Difficulty'] == 'hard']
hard_data = hard_data.sort_values(by='Time Stamp')

fig = go.Figure()

fig.add_trace(go.Scatter(
    x=hard_data['Time Stamp'],
    y=hard_data['Score'],
    mode='markers+lines',
    marker=dict(size=10, color='red'),
    name='Score for Hard Difficulty'
))

fig.update_layout(
    title='Score over Time for Hard Difficulty',
    xaxis_title='Time Stamp',
    yaxis_title='Score',
    hovermode='closest'
)

fig.update_xaxes(
    dtick="M1",
    tickformat="%Y-%m-%d %H:%M",
    tickangle=45
)

fig.update_yaxes(
    rangemode="tozero"
)

fig.update_traces(
    line=dict(dash='solid')
)

fig.show()