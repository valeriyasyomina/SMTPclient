from graphviz import Digraph
import re, sys

reFsm = re.compile('^\s*\{\s*tst\s*=(.+?);\s*tev\s*=(.+?;)\s*next\s*=(.+?);\s*\}.*$')
reSubTev = re.compile('(.+?)[,;]')

def fsmToGraph(filenameFrom, filenameTo):
    file = open(filenameFrom, 'r')
    openFilelines = file.readlines()
    file.close()

    srcTotal = set()
    edges = []

    f = Digraph('finite_state_machine', filename=filenameTo)

    for line in openFilelines:
        m = reFsm.match(line)
        if m:
            curSrc = m.group(1).strip()
            curDst = m.group(3).strip()
            curEvn = reSubTev.findall(m.group(2).strip())

            for el in curEvn:
                edges.append({
                    'src': curSrc,
                    'evn': el.strip(),
                    'dst': curDst
                })

            if (curSrc != '"*"') and (curSrc not in srcTotal):
                srcTotal.add(curSrc)

    for el in edges:
        if (el['src'] != '"*"'):
            f.edge(el['src'], el['dst'], label=el['evn'])
        else:
            for curSrcEl in srcTotal:
                f.edge(curSrcEl, el['dst'])

    f.render()

def main():
    fsmToGraph(sys.argv[1], sys.argv[2])
  # fsmToGraph('../server.def', 'server.gr')

if __name__ == "__main__":
    # if you call this script from the command line (the shell) it will
    # run the 'main' function
    main()