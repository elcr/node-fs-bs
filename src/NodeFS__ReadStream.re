open Relude.Globals;


[@bs.module "fs"]
external _createReadStream: string => NodeStream.Readable.t = "createReadStream";


let make = path =>
    IO.async(resolve => {
        let stream = _createReadStream(path);
        NodeStream.Readable.on(
            `error(exc =>
                NodeFS__Error.fromException(exc)
                    |. Error
                    |> resolve
            ),
            stream
        );
        NodeStream.Readable.on(
            `ready(() =>
                Ok(stream)
                    |> resolve
            ),
            stream
        )
    });
