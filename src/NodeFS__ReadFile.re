open Relude.Globals;

module Error = NodeFS__Error;


type _readFileOptions = {
    encoding: string
};


[@bs.module "fs"]
external _readFile : (
    string,
    _readFileOptions,
    (Js.Null.t(Js.Exn.t), string) => unit
) => unit = "readFile";


let readFile = (~encoding="utf-8", path) =>
    IO.async(resolve =>
        _readFile(path, { encoding: encoding }, (error, contents) =>
            Js.Null.toOption(error)
                |> Result.fromOption(contents)
                |> Result.flip
                |> Result.mapError(Error.fromException)
                |> resolve
        )
    );
