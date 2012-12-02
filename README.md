template
========

This is my template project. Lately, most of my C projects look the same. So,
to save me from some serious work (setting up XCode projects is a nightmare)
I made this little template and supplied a script to do all the neccessary
substitutions.

Usage
-----

### Initial setup:

Just clone the template project and call the `subst.sh` script. The script
takes a single parameter: The name for your new project. It uses `git config`
to determine your name and email, and inserts the current year into all license
templates (which are BSD, by the way).

    git clone git@github.com:jpommerening/template.git myproject
    cd myproject
    ./subst.sh myproject
    git commit

### Pulling updates:

After doint it's substitutions and renaming, the script commits all modified files
and renames `origin` to `template`.

So, assuming you´re on the `master` branch, if you want to pull updates (in many
cases this might actually work, because `git` is awesome) just use the following
command:

    git pull template master


License
-------

Copyright &copy; @YEAR@, @NAME@ <@EMAIL@>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1.  Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer. 
2.  Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.