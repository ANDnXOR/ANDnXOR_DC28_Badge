for i in source/PIX/*; do
	new_path=$(echo $i | sed '0,/source/s//image/')
	raw_path=${new_path%.*}.RAW
	
	./to_raw.sh $i $raw_path
done

for i in source/BLING_BW/*; do
	new_path=$(echo $i | sed '0,/source/s//image/')
	raw_path=${new_path%.*}.RAW
	
	./to_raw_bw.sh $i $raw_path
done
