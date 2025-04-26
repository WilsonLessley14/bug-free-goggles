# reads the specified glsl file, and outputs a single line string that openGL can compile

SHADER_DIRECTORY_PATH="../shaders/"
FILENAME="$1"

if [[ -z "$FILENAME" ]]; then
  echo "Usage: $0 <filename>"
  exit 1
fi

GLSL_FILE="$SHADER_DIRECTORY_PATH$FILENAME"

if [[ -f "$GLSL_FILE" ]]; then
  # define aggregation string
  aggregated=""
  # read the file line by line
  while IFS= read -r line || [[ -n "$line" ]]; do

    # trim leading and trailing whitespace
    trimmed=$(echo "$line" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')

    # skip empty lines
    if [[ -n "$trimmed" ]]; then
      aggregated+="\"$line\n\""
    fi
  done < "$GLSL_FILE"

  printf "%s" "$aggregated"
  echo ""
else
  echo "file $GLSL_FILE does not exist."
fi
