for i = 1:length(image_data)
    [~,name,~] = fileparts(image_data(i).name);
    imwrite(image_data(i).image, ['./ppm/',name, '.ppm']);
    
end