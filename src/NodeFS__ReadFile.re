open Relude.Globals;

module Error = NodeFS__Error;
module Utils = NodeFS__Utils;


type _readFileOptions = {
    withFileTypes: bool,
    encoding: string
};


[@bs.module "fs"]
external _readFile : (
    string,
    _readFileOptions,
    (Js.Nullable.t(Js.Exn.t), string) => unit
) => unit = "readFile";


let readFile = (~encoding="utf-8", path) => {
    let io = Relude.Js.Promise.toIOLazy(() => {
        Utils.makePromise((resolve, reject) => {
            _readFile(path, { withFileTypes: true, encoding }, (error, contents) => {
                let result = Js.Nullable.toOption(error)
                    |> Result.fromOption(contents)
                    |> Result.flip;
                switch (result) {
                    | Ok(contents) => resolve(contents)
                    | Error(error) => reject(error)
                }
            })
        })
    });
    IO.mapError(promiseError => {
        Utils.promiseErrorToException(promiseError)
            |> Error.fromException
    }, io)
};
