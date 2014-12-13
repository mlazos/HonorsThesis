function adjmat = filladjmat( row, col, row_dim, col_dim, adjmat)

adj_row = rowColToInd(row, col, col_dim);

if(col > 1)
    adj_col = rowColToInd(row, col - 1, col_dim);
    adjmat(adj_row, adj_col) = 1;
    adjmat(adj_col, adj_row) = 1;
end

if(col < col_dim)
    adj_col = rowColToInd(row, col + 1, col_dim);
    adjmat(adj_row, adj_col) = 1;
    adjmat(adj_col, adj_row) = 1;
end

if(row > 1)
    adj_col = rowColToInd(row - 1, col, col_dim);
    adjmat(adj_row, adj_col) = 1;
    adjmat(adj_col, adj_row) = 1;
end

if(row < row_dim)
    adj_col = rowColToInd(row + 1, col, col_dim);
    adjmat(adj_row, adj_col) = 1;
    adjmat(adj_col, adj_row) = 1;
end


end



