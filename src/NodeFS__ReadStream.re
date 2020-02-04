open Relude.Globals;

module Error = NodeFS__Error;
module Utils = NodeFS__Utils;


type t;


[@bs.send.pipe: t]
external _onError: (string, Js.Exn.t => unit) => unit = "on";


[@bs.send.pipe: t]
external _onReady: (string, unit => unit) => unit = "on";


[@bs.module "fs"]
external _createReadStream: string => t = "createReadStream";


let make = path =>
    Relude.Js.Promise.toIOLazy(() =>
        Utils.makePromise((resolve, reject) => {
            let stream = _createReadStream(path);
            _onError("error", reject, stream);
            _onReady("ready", resolve, stream)
        })
    )
    |> IO.mapError(promiseError =>
        Utils.promiseErrorToException(promiseError)
            |> Error.fromException
    );
