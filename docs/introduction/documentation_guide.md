# Documentation Guide

This guide outlines the process for contributing to and maintaining the documentation. All documentation resides within the `docs` directory of the GitHub repository. We leverage ReadTheDocs ([https://readthedocs.org/](https://readthedocs.org/)) for documentation generation and the Material for MkDocs theme ([https://squidfunk.github.io/mkdocs-material/](https://squidfunk.github.io/mkdocs-material/)) for a polished and consistent user experience.

## Setting Up Your Local Environment

To work on the documentation locally:

### **Install Python 3:**

Ensure Python 3 is installed and accessible on your system. Verify by running:

```bash
python3 --version
```

### **Run the ****`install.sh`**** Script:**

Navigate to the `docs` directory and run the script, which installs the virtual environment for Python 3, clones required repositories, and sets up the necessary directories.
After running the script, activate the virtual environment:

```bash
cd ./docs
./install.sh
source ./activate.sh
```

### **Build and Serve Documentation:**

Now you can run the `build_docs.sh` script, which builds the documentation and runs the server:

```bash
./build_docs.sh
```

Alternatively, you can directly use MkDocs:

```bash
mkdocs serve
```

Access the documentation in your web browser at http://localhost:8000/rdkcentral/rdk-halif-aidl/. The site will automatically reload when changes are made to the Markdown files in the `docs` directory.

## Structuring the Documentation

The `mkdocs.yml` file, located at the root of the repository, is crucial for defining the documentation's structure and navigation. This file dictates the hierarchy of pages and how they are linked. **Any additions or removals of documentation pages require a corresponding update to ****`mkdocs.yml`**** to maintain proper navigation.**

See [For information on the the naming conventions used see:-](../halif/key_concepts/hal/hal_naming_conventions.md)

## Automatic Deployment

A GitHub Actions workflow is configured to automatically deploy the latest documentation to GitHub Pages at [https://rdkcentral.github.io/rdk-halif-aidl/](https://rdkcentral.github.io/rdk-halif-aidl/). The website's source code resides in the `gh-pages` branch of the repository.

## Writing Style and Guidelines

When contributing to the documentation, please adhere to the following guidelines:

- **Accuracy and Clarity:** Ensure all information is accurate, up-to-date, and easy to understand. Use clear and concise language.
- **Proofreading:** Thoroughly proofread all content for spelling, grammar, and punctuation errors before submitting changes.
- **Admonitions for Emphasis:** Use admonitions to highlight key information, warnings, notes, or tips. Material for MkDocs provides various admonition styles: [https://squidfunk.github.io/mkdocs-material/reference/admonitions/](https://squidfunk.github.io/mkdocs-material/reference/admonitions/)

!!! note "Helpful Tip"
    This is an example of a note admonition.

!!! warning "Important Consideration"
    This is a warning!

- **Code Blocks with Syntax Highlighting:** Always use code blocks for code examples and specify the language for syntax highlighting:

```python
def example_function():
    print("Hello, world!")
```

```javascript
function exampleFunction() {
    console.log("Hello, world!");
}
```

- **MkDocs-Material Reference:** Refer to the official Material for MkDocs documentation for advanced features and customization options: [https://squidfunk.github.io/mkdocs-material/reference/](https://squidfunk.github.io/mkdocs-material/reference/)

- **Mermaid Diagrams (Preferred):** Use Mermaid ([https://mermaid.js.org/](https://mermaid.js.org/)) for creating diagrams whenever possible. Mermaid diagrams offer better accessibility, performance, and scalability compared to embedded images.

```mermaid
graph LR
    A[Start] --> B{Is there an Error?};
    B -- Yes --> C[Debug];
    C --> D[Test];
    D --> B;
    B -- No --> E[Success!];
```

This guide ensures consistency, accuracy, and usability across all documentation contributions.
