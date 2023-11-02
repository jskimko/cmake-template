#!/usr/bin/env bash

if [ ! -d src ]; then
  echo "error: must run from root directory" >&2
  exit 2
fi

if [ $# -ne 1 ]; then
  echo "usage: $0 new_name" >&2
  exit 1
fi

new_name=$1
if ! echo "$new_name" | grep -Eq '^[a-z]*$'; then
  echo "error: new name must match '^[a-z]*$'" >&2
  exit 3
fi

upper=$(echo $new_name | tr [:lower:] [:upper:])
lower=$(echo $new_name | tr [:upper:] [:lower:])

if [ -d '.git' ]; then
  git=git
fi

for f in $(grep -irl xxx --exclude-dir='build' --exclude-dir='.*'); do
  bname=$(basename "$f")
  if echo "$bname" | grep -Eq '^\.'; then
    continue
  fi

  echo "Updating $bname"
  sed -i "s/xxx/$lower/g" "$f"
  sed -i "s/XXX/$upper/g" "$f"
done

for f in $(find . -type f -iname '*xxx*' -not -path './build*'); do
  $git mv $f $(echo $f | sed "s:/\([^/]*\)xxx\([^/]*\)$:/\1${lower}\2:")
done

for f in $(find . -type d -iname '*xxx*' -not -path './build*'); do
  $git mv $f $(echo $f | sed "s:xxx:${lower}:")
done

echo
echo "Remove this script with \`[git] rm $0\`"
