import pandas as pd
import plotly.graph_objs as go

df = pd.read_csv('game_data.csv')


df['Time Stamp'] = pd.to_datetime(df['Time Stamp'])

easy_data = df[df['Difficulty'] == 'easy']
easy_data = easy_data.sort_values(by='Time Stamp')


fig = go.Figure()

fig.add_trace(go.Scatter(
    x=easy_data['Time Stamp'],
    y=easy_data['Score'],
    mode='markers+lines',
    marker=dict(size=10, color='blue'),
    name='Score for Easy Difficulty'
))

fig.update_layout(
    title='Score over Time for Easy Difficulty',
    xaxis_title='Time Stamp',
    yaxis_title='Score',
    hovermode='closest'
)


fig.show()
