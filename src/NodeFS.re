// open Rebase;





// module ReadDir = {

// };


// module ReadFile = {
//     type error =
//         | AccessDenied
//         | DoesNotExist
//         | NotAFile
//         | UnknownError;

//     [@bs.module "fs"]
//     external _readFile : (
//         string,
//         {. "encoding": string },
//         (Js.Nullable.t(systemError), string) => unit
//     ) => unit = "readFile";

//     let readFile = path => {
//         Future.make(resolve => {
//             _readFile(path, { "encoding": "utf8" }, (error, contents) => {
//                 Caml_option.nullable_to_opt(error)
//                     |> Option.map(error => {
//                         switch (error##code) {
//                             | "EACCES" | "EPERM" => Error(AccessDenied)
//                             | "ENOENT" => Error(DoesNotExist)
//                             | "EISDIR" => Error(NotAFile)
//                             | _ => Error(UnknownError)
//                         }
//                     })
//                     |> Option.getOr(Ok(contents))
//                     |> resolve
//             })
//         })
//     };
// };
