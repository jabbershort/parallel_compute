import json
import os
from tabulate import tabulate

folder_path = os.path.dirname(os.path.realpath(__file__))

header = ["Board Name", "Board Core and Frequency", "Board Score"]

with open(os.path.join(folder_path,'benchmarks.json'),'r') as fp:
    data = json.load(fp)
board_defaults = [board for board in data if board['default']]
board_defaults = sorted(board_defaults,key=lambda d: d['score'])

print("Board defaults")
rows = [[f'{board["board"]}',f'({board["core"]} @ {board["frequency (MHz)"]}MHz)',f'{board["score"]}'] for board in board_defaults]
print(tabulate(rows,header))

print("")
print("")

board_names = [board["board"] for board in board_defaults]

board_maximums = []
for board_name in board_names:
    max_item = max([board for board in data if board["board"] == board_name],key=lambda x:x["score"])
    board_maximums.append(max_item)

board_maximums = sorted(board_maximums,key=lambda d:d["score"])
rows = [[f'{board["board"]}',f'({board["core"]} @ {board["frequency (MHz)"]}MHz)',f'{board["score"]}'] for board in board_maximums]
print(tabulate(rows,header))
