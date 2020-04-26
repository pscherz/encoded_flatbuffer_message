currentBuild.description = "build messages here:\n"

node 'any' {
	stage('something') {
		echo('hello');
		currentBuild.description += "done with step 'something'\n";
	}

	stage('something else'){
		echo('something else');
		currentBuild.description += "done with step 'else'\n";
	}

	stage('ffff') {
		echo('dd');
		currentBuild.description += "done with step 'ffff'\n";
	}

	stage('ggg') {
		echo('ggg');
		currentBuild.description += "done with step 'ggg'\n";
	}
}
