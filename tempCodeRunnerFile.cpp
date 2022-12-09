            }
            else {
                temp += toDecode[i];
            }
        } 

        // for (int i = 0; i < temp.length(); i++){
        //     for (int j = 0; j < sizeof(encode_table); j++){
        //         if (encode_table[j] == temp[i]){
        //             switch (j%3){
        //                 case 0:
        //                     char decoded_char; 
        //                     decoded_char = (encode_table[j] << 6) & bitmaskSet3. + encode_table[j+1] >> 6;
        //                     cout << decoded_char;
        //                 break;
                    
        //                 case 1:

        //                 break;

        //                 case 2:

        //                 break;
        //             }
        //         }
        //     }
        // }

    
        for (int i=0; i < temp.length(); i++) {
            int num = temp[i];
            // cout << num << ", ";
            switch (i%3){