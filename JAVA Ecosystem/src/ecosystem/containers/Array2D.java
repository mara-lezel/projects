package ecosystem.containers;

import java.io.Serializable;
import java.util.Iterator;

/**
 * <pre>
 * Parameterized container for 2D object arrays.
 *  Array size is fixed and cannot be resized.
 *  Container supports get and set operations.
 *
 *  Iterator moves in forward direction and allows
 *  read operations.
 *
 *  Iterator removes objects by marking them as null.
 *  </pre>
 */
public class Array2D<Type> implements Iterable<Type>, Serializable
{
    public Array2D(Type[][] array)
    {
        if (array == null)
            throw new NullPointerException();

        this.array = array;
        this.columns = array.length;
        this.rows = array[0].length;
    }

    public Type get(int i, int j)
    {
        if(i < 0 || i >= columns || j < 0 || j >= rows)
            throw new IndexOutOfBoundsException();

        return array[i][j];
    }

    public void set(int i, int j, Type element)
    {
        if(i < 0 || i >= columns || j < 0 || j >= rows)
            throw new IndexOutOfBoundsException(i + " " + j);

        array[i][j] = element;
    }

    /** Generic method returning iterator for Array2D class. */
    public Iterator<Type> iterator()
    {
        return new Iterator<Type>()
        {
            private int columnIndex = 0;
            private int rowIndex = -1;

            public boolean hasNext()
            {
                return (columnIndex < columns - 1 || rowIndex < rows - 1) && array[columnIndex] != null;
            }

            public Type next()
            {
                if(rowIndex == rows - 1)
                {
                    rowIndex = 0;
                    return array[++columnIndex][rowIndex];
                }
                return array[columnIndex][++rowIndex];
            }

            public void remove()
            {
                next();
                set(columnIndex, rowIndex, null);
            }
        };
    }

    private Type[][] array;
    private int columns;
    private int rows;
}
