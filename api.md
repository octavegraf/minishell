# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`struct `[`s_cmd`](#structs__cmd) | Command structure containing all the information needed to execute a command.
`struct `[`s_data`](#structs__data) | Core structure handling all the elements used in the program.
`struct `[`s_env`](#structs__env) | Chained list that handle the environment variables.
`struct `[`s_redir`](#structs__redir) | List of all the redirections to do before executing the command.
`struct `[`s_token`](#structs__token) | Structure to handle the pretokenization to tokenization phase.
`struct `[`s_tree`](#structs__tree) | @LinoaSaga je te laisse le faire
`struct `[`s_tree::u_tree::s_tree_cmd`](#structs__tree_1_1u__tree_1_1s__tree__cmd) | 
`struct `[`s_tree::u_tree::s_tree_pipe`](#structs__tree_1_1u__tree_1_1s__tree__pipe) | 
`struct `[`s_tree::u_tree::s_tree_redir`](#structs__tree_1_1u__tree_1_1s__tree__redir) | 
`union `[`s_tree::u_tree`](#unions__tree_1_1u__tree) | 

# struct `s_cmd` 

Command structure containing all the information needed to execute a command.

#### Parameters
* `args` Array of arguments for the command. 

* `cmd_path` Path to the command executable. 

* `redirs` List of redirections associated with the command. 

* `next` Next element.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public char ** `[`args`](#structs__cmd_1ab2b785023c02b20f8753559330263481) | 
`public char * `[`cmd_path`](#structs__cmd_1a46368527430eff4e960b66bcd2aa505d) | 
`public `[`t_redir`](#structs__redir)` * `[`redirs`](#structs__cmd_1a73728be10a9ad4337d14343630abf572) | 
`public struct `[`s_cmd`](#structs__cmd)` * `[`next`](#structs__cmd_1a7bd4dbbd332b2cb9c3d85fcb3d2d529f) | 

## Members

#### `public char ** `[`args`](#structs__cmd_1ab2b785023c02b20f8753559330263481) 

#### `public char * `[`cmd_path`](#structs__cmd_1a46368527430eff4e960b66bcd2aa505d) 

#### `public `[`t_redir`](#structs__redir)` * `[`redirs`](#structs__cmd_1a73728be10a9ad4337d14343630abf572) 

#### `public struct `[`s_cmd`](#structs__cmd)` * `[`next`](#structs__cmd_1a7bd4dbbd332b2cb9c3d85fcb3d2d529f) 

# struct `s_data` 

Core structure handling all the elements used in the program.

#### Parameters
* `env` Env structure. 

* `exit_code` Last exit code returned by a command. 

* `inputs` Inputs read by readline. 

* `error_parse` Indicates that an error happened during parsing. 

* `token` Token of the inputs through the tokenization phase.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`t_env`](#structs__env)` * `[`env`](#structs__data_1ae74d75234d9e92b30b55c13c61117d2d) | 
`public int `[`exit_code`](#structs__data_1a9f411dbcaaa97f1417f2913615341cf9) | 
`public char * `[`inputs`](#structs__data_1a7e2af550c1425e0f3f27520072e49653) | 
`public bool `[`error_parse`](#structs__data_1aced13bc66312b4b9ca129cd256db59b7) | 
`public `[`t_token`](#structs__token)` * `[`token`](#structs__data_1a924b2203dcf1ec4ff4435373e087f840) | 

## Members

#### `public `[`t_env`](#structs__env)` * `[`env`](#structs__data_1ae74d75234d9e92b30b55c13c61117d2d) 

#### `public int `[`exit_code`](#structs__data_1a9f411dbcaaa97f1417f2913615341cf9) 

#### `public char * `[`inputs`](#structs__data_1a7e2af550c1425e0f3f27520072e49653) 

#### `public bool `[`error_parse`](#structs__data_1aced13bc66312b4b9ca129cd256db59b7) 

#### `public `[`t_token`](#structs__token)` * `[`token`](#structs__data_1a924b2203dcf1ec4ff4435373e087f840) 

# struct `s_env` 

Chained list that handle the environment variables.

#### Parameters
* `name` Name of the environment variable. 

* `value` Value of the environment variable. 

* `next` Next element.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public char * `[`name`](#structs__env_1aa96c840f2a36e2c836ab89ed924d8b93) | 
`public char * `[`value`](#structs__env_1aeed22f6fb6689d3a190d64d3e11d989f) | 
`public struct `[`s_env`](#structs__env)` * `[`next`](#structs__env_1a3caf3df6eb72714ffcd4e22f9c94ecf2) | 

## Members

#### `public char * `[`name`](#structs__env_1aa96c840f2a36e2c836ab89ed924d8b93) 

#### `public char * `[`value`](#structs__env_1aeed22f6fb6689d3a190d64d3e11d989f) 

#### `public struct `[`s_env`](#structs__env)` * `[`next`](#structs__env_1a3caf3df6eb72714ffcd4e22f9c94ecf2) 

# struct `s_redir` 

List of all the redirections to do before executing the command.

#### Parameters
* `type` Type of the redirection. 

* `target` Target of the redirection (what it does depends of redir type). 

* `heredoc_fd` File descriptor for the heredoc.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public t_redir_type `[`type`](#structs__redir_1a312cf0e856ee9976409a20fe44fb4471) | 
`public char * `[`target`](#structs__redir_1a952b0bba8a220539a6bc5a64e9505a5d) | 
`public int `[`heredoc_fd`](#structs__redir_1a9d43b3be04188fa467ff0a8b519c5f5b) | 
`public struct `[`s_redir`](#structs__redir)` * `[`next`](#structs__redir_1a22c2c19d79bcba43a30d098703761422) | 

## Members

#### `public t_redir_type `[`type`](#structs__redir_1a312cf0e856ee9976409a20fe44fb4471) 

#### `public char * `[`target`](#structs__redir_1a952b0bba8a220539a6bc5a64e9505a5d) 

#### `public int `[`heredoc_fd`](#structs__redir_1a9d43b3be04188fa467ff0a8b519c5f5b) 

#### `public struct `[`s_redir`](#structs__redir)` * `[`next`](#structs__redir_1a22c2c19d79bcba43a30d098703761422) 

# struct `s_token` 

Structure to handle the pretokenization to tokenization phase.

#### Parameters
* `type` Preidentified type of the token. 

* `inputs` Text. 

* `quoted` If infos are quoted or not, the type of quote (single/double). 

* `target` Only used in tokenization phase, info of the redirection. 

* `next` Next element. 

* `past` Previous element.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public t_node_type `[`type`](#structs__token_1a8396da6428d6d93765f588643174ee06) | 
`public char * `[`inputs`](#structs__token_1af1d36bf1d0be042077846f8b58c4c0f4) | 
`public char `[`quoted`](#structs__token_1a6fd47f70e7f53a9e626df98451c9e3b7) | 
`public char * `[`target`](#structs__token_1aaf6683296c459725168dd4a91402c52a) | 
`public struct `[`s_token`](#structs__token)` * `[`next`](#structs__token_1a5dae434205818bfc83a61809d4a34a29) | 
`public struct `[`s_token`](#structs__token)` * `[`past`](#structs__token_1ae624ad3dc79d31ca1068ed02bac3ac9c) | 

## Members

#### `public t_node_type `[`type`](#structs__token_1a8396da6428d6d93765f588643174ee06) 

#### `public char * `[`inputs`](#structs__token_1af1d36bf1d0be042077846f8b58c4c0f4) 

#### `public char `[`quoted`](#structs__token_1a6fd47f70e7f53a9e626df98451c9e3b7) 

#### `public char * `[`target`](#structs__token_1aaf6683296c459725168dd4a91402c52a) 

#### `public struct `[`s_token`](#structs__token)` * `[`next`](#structs__token_1a5dae434205818bfc83a61809d4a34a29) 

#### `public struct `[`s_token`](#structs__token)` * `[`past`](#structs__token_1ae624ad3dc79d31ca1068ed02bac3ac9c) 

# struct `s_tree` 

@LinoaSaga je te laisse le faire

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public t_node_type `[`type`](#structs__tree_1a1bb468e9bc707159f50046d14e10a75a) | 
`public union `[`s_tree::u_tree`](#unions__tree_1_1u__tree)` `[`tree`](#structs__tree_1ab48e53514ec80fec5e6cd6b0251c75fb) | 

## Members

#### `public t_node_type `[`type`](#structs__tree_1a1bb468e9bc707159f50046d14e10a75a) 

#### `public union `[`s_tree::u_tree`](#unions__tree_1_1u__tree)` `[`tree`](#structs__tree_1ab48e53514ec80fec5e6cd6b0251c75fb) 

# struct `s_tree::u_tree::s_tree_cmd` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public char * `[`inputs`](#structs__tree_1_1u__tree_1_1s__tree__cmd_1a7a80058578bc1455bd6a76dde45f438a) | 

## Members

#### `public char * `[`inputs`](#structs__tree_1_1u__tree_1_1s__tree__cmd_1a7a80058578bc1455bd6a76dde45f438a) 

# struct `s_tree::u_tree::s_tree_pipe` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public struct `[`s_tree`](#structs__tree)` * `[`left`](#structs__tree_1_1u__tree_1_1s__tree__pipe_1a6b79259b7a346b12994323e6f96d9cb5) | 
`public struct `[`s_tree`](#structs__tree)` * `[`right`](#structs__tree_1_1u__tree_1_1s__tree__pipe_1ab642b8d5af110ae3ce9146ae3ccb794b) | 

## Members

#### `public struct `[`s_tree`](#structs__tree)` * `[`left`](#structs__tree_1_1u__tree_1_1s__tree__pipe_1a6b79259b7a346b12994323e6f96d9cb5) 

#### `public struct `[`s_tree`](#structs__tree)` * `[`right`](#structs__tree_1_1u__tree_1_1s__tree__pipe_1ab642b8d5af110ae3ce9146ae3ccb794b) 

# struct `s_tree::u_tree::s_tree_redir` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public t_redir_type `[`type`](#structs__tree_1_1u__tree_1_1s__tree__redir_1a8123317a925001c5560dc8c08e5ca1f3) | 
`public char * `[`target`](#structs__tree_1_1u__tree_1_1s__tree__redir_1ad079edc644948df24e4fd0ce7c999f41) | 
`public struct `[`s_tree`](#structs__tree)` * `[`child`](#structs__tree_1_1u__tree_1_1s__tree__redir_1a3cf2e5030623923a6eda875e79ea748b) | 

## Members

#### `public t_redir_type `[`type`](#structs__tree_1_1u__tree_1_1s__tree__redir_1a8123317a925001c5560dc8c08e5ca1f3) 

#### `public char * `[`target`](#structs__tree_1_1u__tree_1_1s__tree__redir_1ad079edc644948df24e4fd0ce7c999f41) 

#### `public struct `[`s_tree`](#structs__tree)` * `[`child`](#structs__tree_1_1u__tree_1_1s__tree__redir_1a3cf2e5030623923a6eda875e79ea748b) 

Generated by [Moxygen](https://sourcey.com/moxygen)