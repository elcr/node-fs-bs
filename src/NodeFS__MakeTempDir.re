open Relude.Globals;

module Error = NodeFS__Error;


type _mkdtempOptions = {
    encoding: string
};


[@bs.module "fs"]
external _mkdtemp : (
    string,
    _mkdtempOptions,
    (Js.Null.t(Js.Exn.t), string) => unit
) => unit = "mkdtemp";


let makeTempDir = (~encoding="utf-8", path) =>
    IO.async(resolve =>
        _mkdtemp(path, { encoding: encoding }, (error, contents) =>
            Js.Null.toOption(error)
                |> Result.fromOption(contents)
                |> Result.flip
                |> Result.mapError(Error.fromException)
                |> resolve
        )
    );