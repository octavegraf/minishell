## Project rules
All functions must be commented and countain @ above.
| Tag           | Description                                                                 |
|---------------|-----------------------------------------------------------------------------|
| `@brief`      | Short description, shown in tooltips and summary sections.                  |
| `@param [in] / [out] / [in,out]` | Documents a function parameter: input, output, or both.  |
| `@return`     | Describes the return value of a function.                                   |
| `@note`       | Adds a remark, extra detail, or helpful comment.                            |
| `@pre`        | States preconditions that must hold before calling the function.            |
| `@attention`  | Stronger warning; highlights critical caveats.                              |

## Project clone
Update submodule to latest commit:
```shell
git submodule update --remote
```
Download all submodules:
```shell
git submodule update --init --recursive
```
Git clone with submodules:
```shell
git clone --recursive https://github.com/octavegraf/minishell
```
Change branch
``` shell
git checkout <branch_name>
```
## Useful links
### [Figma board](https://www.figma.com/board/ZHV4kQ2Qe8JAcvBIfVHMPx/Minishell?node-id=0-1&p=f&t=JD2uosrCLLm5dmlS-0)

### [Github repo](https://github.com/octavegraf/minishell)

### [Project link](https://projects.intra.42.fr/42cursus-minishell/ocgraf)

### [Documentation](/doc/HTML/index.html)