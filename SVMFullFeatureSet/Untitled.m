for i = 120:length(new_image_data)
    [~,name,~] = fileparts(new_image_data(i).name);
    imwrite(new_image_data(i).ground_truth, ['./pbm/',name, '.pbm']);
    
end