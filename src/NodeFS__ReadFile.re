open Relude.Globals;

module Error = NodeFS__Error;


type _readFileOptions = {
    encoding: Js.Null.t(string)
};


[@bs.module "fs"]
external _readText : (
    string,
    _readFileOptions,
    (Js.Null.t(Js.Exn.t), string) => unit
) => unit = "readFile";


[@bs.module "fs"]
external _readBuffer : (
    string,
    _readFileOptions,
    (Js.Null.t(Js.Exn.t), Node.Buffer.t) => unit
) => unit = "readFile";


let _toResult = (error, contents) =>
    Js.Null.toOption(error)
        |> Result.fromOption(contents)
        |> Result.flip
        |> Result.mapError(Error.fromException);


let readText = (~encoding="utf-8", path) =>
    IO.async(resolve =>
        _readText(path, { encoding: Js.Null.return(encoding) }, (error, contents) =>
            _toResult(error, contents)
                |> resolve
        )
    );


let readBuffer = path =>
    IO.async(resolve =>
        _readBuffer(path, { encoding: Js.Null.empty }, (error, contents) =>
            _toResult(error, contents)
                |> resolve
        )
    );
