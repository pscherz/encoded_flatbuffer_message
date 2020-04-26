currentBuild.description = "build messages here:\n"

node 'any' {
	stage('something') {
		stage('something') {
			steps {
				echo 'hello'
				currentBuild.description += "done with step 'something'\n"
			}
		}

		stage('else') {
			steps {
				echo 'something else'
				currentBuild.description += "done with step 'else'\n"
			}
		}
	}

	stage('something else in parallel') {
		stage('ffff') {
			steps {
				echo 'dd'
				currentBuild.description += "done with step 'ffff'\n"
			}
		}

		stage('ggg') {
			steps {
				echo 'ggg'
				currentBuild.description += "done with step 'ggg'\n"
			}
		}
	}
}
