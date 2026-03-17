# **Fork-Based Contribution Guide: Forking for External Contributions**

## **Introduction**

Welcome to the Fork-Based Contribution Guide! This guide is designed for engineers, integrators, and third-party developers who contribute to the project without having direct write access to the main repository. Forking enables you to build, test, and propose enhancements in a safe and controlled manner, consistent with RDK Central’s collaborative development model.

## **What is Forking?**

Forking creates a personal copy of the main repository under your GitHub account. This isolated copy allows you to make changes independently, experiment freely, and prepare contributions without affecting the core codebase.

## **Why Fork?**

* **Safe Experimentation:** Work on new features or fixes without risk to the core repository.
* **Clear Contribution Pathway:** Submit your work through pull requests to be reviewed and potentially merged into the main project.
* **Decentralized Collaboration:** Forking supports scalable open-source workflows where multiple organizations contribute independently.

## **Step-by-Step Forking Workflow**

1. **Find the Repository:** Navigate to the official project repository on GitHub.
2. **Click “Fork”:** Located in the upper-right of the repository page.
3. **Choose Your Account:** Select your GitHub account to host the fork.
4. **Clone Your Fork Locally:**

   ```bash
   git clone https://github.com/<your-username>/<repository-name>.git
   ```

5. **Create a Branch:** (Highly recommended) Create a topic branch for your changes:

   ```bash
   git checkout -b feature/my-new-feature
   ```

6. **Make Your Changes:** Modify files to add features, fix bugs, or update documentation.
7. **Commit Your Changes:** Write meaningful and descriptive commit messages:

   ```bash
   git commit -m "Add feature: <short description>"
   ```

8. **Push to Your Fork:**

   ```bash
   git push origin feature/my-new-feature
   ```

9. **Open a Pull Request:** Go to the original repository and submit a pull request from your fork. Include a clear explanation of your changes and their purpose.
10. **Review & Feedback:** Core Development Team members will review your pull request. Feedback may be provided to align your contribution with project standards before it is accepted.

## **Important Considerations**

* **Stay Synced:** Regularly update your fork from the upstream repository to avoid merge conflicts.
* **Communicate Clearly:** Explain the scope, motivation, and impact of your contribution in the pull request.
* **Be Patient and Collaborative:** Reviews take time. Be receptive to feedback and willing to revise.
* **Follow Standards:** Adhere to the project's coding, testing, and documentation practices.

For more detailed information, refer to the [RDK Central Contribution Guide](https://developer.rdkcentral.com/support/support/articles/how_to_contribute/)
