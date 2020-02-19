open Relude.Globals;

module Error = NodeFS__Error;
module Utils = NodeFS__Utils;


[@bs.module "fs"]
external _createReadStream: string => NodeStream.Readable.t = "createReadStream";


let make = path =>
    Relude.Js.Promise.toIOLazy(() =>
        Utils.makePromise((resolve, reject) => {
            let stream = _createReadStream(path);
            NodeStream.Readable.on(`error(reject), stream);
            NodeStream.Readable.on(`ready(() => resolve(stream)), stream);
        })
    )
    |> IO.mapError(promiseError =>
        Utils.promiseErrorToException(promiseError)
            |> Error.fromException
    );
