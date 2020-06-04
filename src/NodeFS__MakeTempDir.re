open Relude.Globals;


type _mkdtempOptions = {
    encoding: string
};


[@bs.module "fs"]
external _mkdtemp : (
    string,
    _mkdtempOptions,
    (Js.Null.t(Js.Exn.t), string) => unit
) => unit = "mkdtemp";


let makeTempDir = (~encoding="utf-8", prefix) =>
    IO.async(resolve =>
        _mkdtemp(prefix, { encoding: encoding }, (error, contents) =>
            Js.Null.toOption(error)
                |> Result.fromOption(contents)
                |> Result.flip
                |> Result.mapError(NodeFS__Error.fromException)
                |> resolve
        )
    );
