using System;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

using AppSecInc.Wix.Extensions;
using Microsoft.Tools.WindowsInstallerXml;

[assembly: AssemblyTitle("AppSecInc WIX JavaTools Extension")]
[assembly: AssemblyDefaultWixExtension(typeof(JavaToolsExtension))]
