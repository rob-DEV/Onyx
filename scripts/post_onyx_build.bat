xcopy "$(SolutionDir)bin\onyx\$(Configuration)\onyx.dll" "$(SolutionDir)bin\onyx-sandbox\$(Configuration)\onyx.dll" /Y &&  
xcopy "$(SolutionDir)bin\onyx\$(Configuration)\onyx.lib" "$(SolutionDir)bin\onyx-sandbox\$(Configuration)\onyx.lib" /Y &&  
xcopy "$(SolutionDir)bin\onyx\$(Configuration)\onyx.pdb" "$(SolutionDir)bin\onyx-sandbox\$(Configuration)\onyx.pdb" /Y && 
xcopy "$(SolutionDir)bin\onyx\$(Configuration)\onyx.dll" "$(SolutionDir)bin\Onyx-Editor\$(Configuration)\onyx.dll" /Y &&  
xcopy "$(SolutionDir)bin\onyx\$(Configuration)\onyx.lib" "$(SolutionDir)bin\Onyx-Editor\$(Configuration)\onyx.lib" /Y &&  
xcopy "$(SolutionDir)bin\onyx\$(Configuration)\onyx.pdb" "$(SolutionDir)bin\Onyx-Editor\$(Configuration)\onyx.pdb" /Y