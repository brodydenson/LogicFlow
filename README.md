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

- [logic_flow-v1.0.0-macos.zip](https://github.com/chipwy/LogicFlow/actions/runs/9424315128/artifacts/1580908724)
- [logic_flow-v1.0.0-linux.zip](https://github.com/chipwy/LogicFlow/actions/runs/9424315128/artifacts/1580908726)
- [logic_flow-v1.0.0-windows.zip](https://github.com/chipwy/LogicFlow/actions/runs/9424315128/artifacts/1580908728)

## Installation

### macOS

1. Download the `logic_flow-v1.0.0-macos.zip` file.
2. Extract the zip file.
3. Run the executable.

### Linux

1. Download the `logic_flow-v1.0.0-linux.zip` file.
2. Extract the zip file.
3. Run the executable.

### Windows

1. Download the `logic_flow-v1.0.0-windows.zip` file.
2. Extract the zip file.
3. Run the executable.
