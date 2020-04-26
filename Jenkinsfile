pipeline {
  agent any
  stages {
    stage('something') {
      parallel {
        stage('something') {
          steps {
            echo 'hello'
          }
        }

        stage('else') {
          steps {
            echo 'something else'
          }
        }

      }
    }

    stage('ffff') {
      parallel {
        stage('ffff') {
          steps {
            echo 'dd'
          }
        }

        stage('ggg') {
          steps {
            echo 'ggg'
          }
        }

      }
    }

  }
}