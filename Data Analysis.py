import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.dates import DateFormatter
import matplotlib.dates as mdates
from mplcursors import cursor

df = pd.read_csv('game_data.csv')

df['Time Stamp'] = pd.to_datetime(df['Time Stamp'])

def plot_difficulty(difficulty):
    data = df[df['Difficulty'] == difficulty]
    data = data.sort_values(by='Time Stamp')

    fig, ax = plt.subplots()

    ax.plot(data['Time Stamp'], data['Score'], marker='o', label=f'{difficulty} Difficulty')

    ax.xaxis.set_major_formatter(DateFormatter("%Y-%m-%d %H:%M"))
    ax.xaxis.set_major_locator(mdates.MinuteLocator(interval=30))
    plt.xticks(rotation=45)

    plt.xlabel('Time Stamp')
    plt.ylabel('Score')
    plt.title(f'Score over Time for {difficulty} Difficulty')
    plt.legend()

    crs = cursor(ax, hover=True)
    @crs.connect("add")
    def on_add(sel):
        sel.annotation.set_text(f'{data.iloc[sel.target.index]["Time Stamp"]}\nScore: {data.iloc[sel.target.index]["Score"]}')
        plt.draw()
        sel.annotation.get_bbox_patch().set_facecolor('yellow')
        sel.annotation.get_bbox_patch().set_alpha(0.4)
        sel.annotation.set_fontsize(10)
        sel.annotation.set_fontweight('bold')
        sel.annotation.set_bbox(dict(boxstyle='round,pad=0.5', edgecolor='black', facecolor='white', alpha=0.5))
        sel.annotation.set_zorder(10)
        plt.pause(0.1)

    fig.autofmt_xdate()
    plt.tight_layout()
    plt.grid(True)
    plt.minorticks_on()
    ax.grid(which='major', linestyle='-', linewidth='0.5', color='blue')
    ax.grid(which='minor', linestyle=':', linewidth='0.5', color='black')
    plt.subplots_adjust(left=0.1, bottom=0.2, right=0.9, top=0.9, wspace=0.4, hspace=0.4)
    ax.tick_params(axis='x', which='major', labelsize=8)
    ax.tick_params(axis='y', which='major', labelsize=8)
    plt.subplots_adjust(left=0.2, bottom=0.3, right=0.8, top=0.8, wspace=0.2, hspace=0.2)
    plt.subplots_adjust(left=0.25, bottom=0.35, right=0.75, top=0.75, wspace=0.25, hspace=0.25)
    plt.subplots_adjust(left=0.15, bottom=0.25, right=0.85, top=0.85, wspace=0.15, hspace=0.15)
    plt.subplots_adjust(left=0.05, bottom=0.15, right=0.95, top=0.95, wspace=0.05, hspace=0.05)
    plt.subplots_adjust(left=0.3, bottom=0.4, right=0.7, top=0.6, wspace=0.3, hspace=0.3)
    plt.subplots_adjust(left=0.35, bottom=0.45, right=0.65, top=0.55, wspace=0.35, hspace=0.35)
    plt.subplots_adjust(left=0.4, bottom=0.5, right=0.6, top=0.5, wspace=0.4, hspace=0.4)
    plt.subplots_adjust(left=0.45, bottom=0.55, right=0.55, top=0.45, wspace=0.45, hspace=0.45)
    plt.subplots_adjust(left=0.5, bottom=0.6, right=0.5, top=0.4, wspace=0.5, hspace=0.5)
    plt.subplots_adjust(left=0.55, bottom=0.65, right=0.45, top=0.35, wspace=0.55, hspace=0.55)
    plt.subplots_adjust(left=0.6, bottom=0.7, right=0.4, top=0.3, wspace=0.6, hspace=0.6)
    plt.subplots_adjust(left=0.65, bottom=0.75, right=0.35, top=0.25, wspace=0.65, hspace=0.65)
    plt.subplots_adjust(left=0.7, bottom=0.8, right=0.3, top=0.2, wspace=0.7, hspace=0.7)
    plt.subplots_adjust(left=0.75, bottom=0.85, right=0.25, top=0.15, wspace=0.75, hspace=0.75)
    plt.subplots_adjust(left=0.8, bottom=0.9, right=0.2, top=0.1, wspace=0.8, hspace=0.8)
    plt.subplots_adjust(left=0.85, bottom=0.95, right=0.15, top=0.05, wspace=0.85, hspace=0.85)

    plt.show()

for difficulty in df['Difficulty'].unique():
    plot_difficulty(difficulty)
