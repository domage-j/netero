
First off, I am very happy that you read this! Because the project is in a very
early stage, any contributions would help a lot. Thank you for taking the time to contribute!

# How can I contribute ?

This section guide you in the process of submiting features, enhancement and bug report.
Everythings is tracked using github issues. You will find related template while opening
issues.

## How to submit a bug report ?

Open an issue using the bug_report template:
 - Use a clear and self descriptive title, please include [bug] in the title.
 - follow the step described in the template
 - If the problem was not triggered or raise by tests make sure you provide clear steps
to reproduce the bug, you also can provide a code snippet test to be include in unit test

## How to request a feature or provide a suggestion ?

Open an issue using the feature_request template:
 - Include in the title a [request] tag
 - Provide a step by step description of the suggest enhencement
 - You may explain why this enhancement would be usefull if it's not obvious

## Your first code contribution

Unsure where to begin ? You can start by looking at the issues, some of them may have
some tag like `beginner` and `help-wanted`. Those tags are there to explicitly
mark the issue as not assigned.

Issue with `beginner` tag are more likely to do not require a good knowlodge about
all the containers of the library. And might be more easier to accomplish.

## Submit a pull request

1. open a pull request using the template
2. Complete the necessary section in the template, do not forget to reference an issue if necessary
3. Make sure the code you add include test and related documentation
4. After submiting the pull request make sure the pipeline didn't failed
5. It this possible that maintainers ask you or performe necessary change before the pull request is merged

If the pipeline failed and you belived this is not related to your contribution please comment it and explain it.
This would help a lot maintainer to find the bug and treat it as a seperat issue.

# How to execute unit test ?

The project is connected to a circle-ci pipeline, every push event trigger the pipeline.
In order to be accepted a pull request must pass all tests successfully. 

The pipeline is executed in a docker container, you can run the tests localy:
 - Using `docker-compose up` this will execute the pipeline locally in a docker container.
 - Using the `make test` rule. This will execute the test on your local machine using your environment.

It is a good idea to test with this two methods especially if your are not working on a linux machine.

