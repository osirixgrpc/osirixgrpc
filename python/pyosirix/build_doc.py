def make_pdoc():
    import pdoc
    import sys
    from os import path, makedirs
    libpath = '/Users/admintmun/dev/pyosirix/osirix'
    if path.exists(libpath):
        sys.path.append(libpath)
    # pdoc.import_path.append(libpath)

    mod = pdoc.import_module('osirix')
    doc = pdoc.Module(mod, allsubmodules=True)
    string = doc.html(external_links=True)
    # Package level
    with open(doc.name + '/Users/admintmun/dev/pyosirix/doc_test/index.html', 'w') as html_file:
        html_file.write(string.encode('utf-8'))

    # Sublevel 1
    for submodule in doc.submodules():
        string = submodule.html(external_links=True)
        if submodule.is_package():
            exte = '/index.html'
        else:
            exte = '.m.html'
        dpath = (submodule.name.split('.')[0] + '/_doc/' +
                 submodule.name.split('.')[-1]) + '/'
        if not path.exists(dpath):
            makedirs(dpath)
        with open(dpath + exte, 'w') as html_file:
            html_file.write(string.encode('utf-8'))
        # Sublevel 2
        # if submodule.submodules():
        #     for subsubmodule in submodule.submodules():
        #         print(subsubmodule.name)
        #         string = subsubmodule.html(external_links=True)
        #         if subsubmodule.is_package():
        #             exte = '.html'
        #         else:
        #             exte = '.m.html'
        #         with open(subsubmodule.name.split('.')[0] + '/_doc/' +
        #                   subsubmodule.name.split('.')[1] + '/' +
        #                   subsubmodule.name.split('.')[-1] +
        #                   exte, 'w') as html_file:
        #             html_file.write(string.encode('utf-8'))

if __name__ == '__main__':
    make_pdoc()