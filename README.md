# Logic Flow
An interpreted language but with cool **sets**.

## Status
Currently in **early** stages of development. 
Thorough documentation will be posted soon...

## Example Code
```
# Returns [1, 2, 3, ... n]
fn range(n) ::
    return { x | x in pZ, x <= n };
;;

let conj = pZ;
for k in range(5)
    conj *= { k*x | x in pZ };
print conj;
```

```
# Returns every subset of the set
fn P(set) ::
    let subsets = {[]};
    for item in set ::
        for subset in subsets
            subsets += {subset ++ item};
        subsets += {[item]};
    ;;
    return subsets;
;;
```

## Downloads

- [logic_flow-v1.0.0-macos.zip](https://github.com/chipwy/LogicFlow/actions/runs/9425529584/artifacts/1581137793)
- [logic_flow-v1.0.0-linux.zip](https://github.com/chipwy/LogicFlow/actions/runs/9425529584/artifacts/1581137794)
- [logic_flow-v1.0.0-windows.zip](https://github.com/chipwy/LogicFlow/actions/runs/9425529584/artifacts/1581137796)

## Installation

### macOS

1. Download the `logic_flow-v1.0.0-macos.zip` file.
2. Extract the zip file.
3. Open up the terminal in the folder's directory.
4. Run `chmod +x logic_flow`.
5. You may need to give the remove the quarantine attribute on the file that MacOS puts. Do so by running `xattr -d com.apple.quarantine logic_flow`.
6. Run the executable in a terminal followed by the .lf file you want to run. EX: `./logic_flow main.lf`.

### Linux

1. Download the `logic_flow-v1.0.0-linux.zip` file.
2. Extract the zip file.
3. Open up the terminal in the folder's directory.
4. Run `chmod +x logic_flow`.
5. Run the executable in a terminal followed by the .lf file you want to run. EX: `./logic_flow main.lf`.

### Windows

1. Download the `logic_flow-v1.0.0-windows.zip` file.
2. Extract the zip file.
3. Open up the terminal in the folder's directory.
4. Run the executable in a terminal followed by the .lf file you want to run. EX: `.\logic_flow main.lf`.
