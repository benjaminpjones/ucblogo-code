# UCBLogo

## Berkeley Logo interpreter

This is a free (both senses) interpreter for the Logo programming language.

The interpreter was written primarily by Daniel Van Blerkom, Brian Harvey,
Michael Katz, Douglas Orleans and Joshua Cogliati. Thanks to Fred Gilham for the X11 code.
Emacs logo-mode by Hrvoje Blazevic.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see https://www.gnu.org/licenses/.

## About this project

This uses the repository https://github.com/jrincayc/ucblogo-code
created for further UCBLogo development.

Changes for this release:
* Added optional object oriented LOGO features ( --enable-objects )
* autoconf based build system
* Variety of bug fixes

Here is an overview of the repository:
* csls - Programs form [Brian Harvey's trilogy "Computer Science Logo Style"](https://people.eecs.berkeley.edu/~bh/).
* docs - Usermanual in variety formats and brief manual page.
* helpfiles - files for UCBLogo interactive help.
* test - Unit tests.
* / - program source code and [a Program Logic Manual](/plm).

The executable file in this distribution includes libraries from the
[wxWidgets project](http://wxwidgets.org/).  The Microsoft Windows version
is distributed with runtime library libgcc_s_dw2-1.dll and libstdc++-6.dll,
from the [MinGW project](http://www.mingw.org/).
Those libraries are also covered by the Gnu GPL.  We
do not distribute their source code; you can download it from their
respective web sites.

## Usage

To build Logo under *nix, install wxWidgets and other dependencies
and then do this:
```
	autoreconf --install
	./configure
	make
```

Note that if you don't have autoconf, the release .tar.gz have already built
configure files.

[UCBLogo Releases](https://github.com/jrincayc/ucblogo-code/releases)

### Building on macOS (Apple Silicon)

The steps above are incomplete on macOS: the wxWidgets autoconf macro and a
couple of build helpers aren't on the default search path, so `configure`
silently disables the GUI and then fails. The block below is a one-shot build
that produces a self-running `UCBLogo.app`. It requires [Homebrew](https://brew.sh).

Copy and paste the whole thing from the root of this repo:

```sh
# 1. Build tools + the wxWidgets GUI library
brew install autoconf automake autoconf-archive wxwidgets texinfo

# 2. Make wxWidgets' and texinfo's helpers visible to the build
#    (wxwin.m4 ships inside the wxwidgets keg, not on aclocal's default path)
export ACLOCAL_PATH="$(dirname "$(find "$(brew --prefix wxwidgets)/share" -name wxwin.m4 | head -1)"):$(brew --prefix)/share/aclocal"
export PATH="$(brew --prefix texinfo)/bin:$PATH"

# 3. Build the interpreter and assemble the app bundle
#    (--disable-docs avoids needing a full TeX install just for the PDF manual)
autoreconf --install --force
./configure --disable-docs
make
make mac

# 4. Run it
open UCBLogo.app
```

On macOS you must launch the `UCBLogo.app` bundle (via `open` or Finder), not
the bare `ucblogo` binary — the bundle is where it finds `logolib` and the
`Messages` file at startup.

## Previous versions

For getting UCBLogo previous versions such as version 6.0 if you're running wxWidgets or 5.4 if not, please visit [Brian Harvey's UCBLogo GitHub repository](https://github.com/brianharvey/UCBLogo).

The distribution for frozen platforms includes version 5.3 for DOS and Mac Classic (pre-OS X) still may be reached at [Brian Harvey's personal page](https://people.eecs.berkeley.edu/~bh/).
