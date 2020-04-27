currentBuild.description = "build messages here:\n"

node 'any' {
	stage('something') {
		echo('hello');
		currentBuild.description += "done with step 'something'\n";

		echo('3');
		currentBuild.description += "done with step '3'\n";

		echo('2');
		currentBuild.description += "done with step '2'\n";

		echo('1');
		currentBuild.description += "done with step '1'\n";

		echo('goodbye');
	}
}
