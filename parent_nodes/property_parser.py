import os

file_path = os.path.join(
    os.path.dirname(
        os.path.dirname(
            os.path.realpath(__file__)
        ))
    ,
    'worker_nodes',
    'board_properties.h'
)

with open(file_path,'r') as fp:
    raw_lines = fp.read()

sections = raw_lines.split('defined')

for section in sections[1:]:
    entry ={}
    lines = section.split('\n')
    for line in lines:
        if 'boardname' in line:
            entry['board'] = line.split('"')[1]
        if 'ADDRESS' in line:
            entry['address'] = int(line.split('=')[1].replace(';',''))

    print(entry)
