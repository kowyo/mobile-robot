#!/bin/sh

branch_file=".last_branch"

if [ -f "$branch_file" ]; then
  branch=$(cat "$branch_file")
else
  # prompt the user to enter the branch name
  echo "Please enter the branch name:"
  read branch
  # save the branch name to the branch file
  echo "$branch" > "$branch_file"
fi

echo "Please choose a commit message:"
echo "1) 🐛 Fixing bugs"
echo "2) ✨ Adding new feature"
echo "3) ⚡ Refactoring code"
echo "4) 🎨 Custom"
read choice

case $choice in
  1) echo "Please enter a description:"; read description; commit_message=":bug: fix: $description";;
  2) echo "Please enter a description:"; read description; commit_message=":sparkles: feat: $description";;
  3) echo "Please enter a description:"; read description; commit_message=":zap: refactor: $description";;
  4) echo "Please enter a commit message:"; read commit_message;;
  *) echo "Invalid choice"; exit 1;;
esac

git add .
git commit -m "$commit_message"

read -r -p "Sync Changes?[Y/n]" input
case $input in
    [yY][eE][sS]|[yY])
        echo "Syncing..."
        git pull origin $branch
        git push origin $branch
        ;;
    [nN][oO]|[nN])
        echo "Exit"
        exit 1
        ;;
    *)
        echo "Invalid input"
        exit 1
        ;;
esac

echo "$branch" > "$branch_file"