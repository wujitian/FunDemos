#ifndef _TARGA_H_
#define _TARGA_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

struct targa_header
{
    unsigned char           id_length;
    unsigned char           cmap_type;
    unsigned char           image_type;
    struct
    {
        unsigned short      cmap_table_offset;
        //unsigned short      cmap_entry_count;         // it seems no use.
        unsigned char       cmap_entry_size;
    } cmap_spec;
    struct
    {
        unsigned short      x_origin;
        unsigned short      y_origin;
        unsigned short      width;
        unsigned short      height;
        unsigned char       bits_per_pixel;
        struct {
            unsigned char   alpha_depth : 4;
            unsigned char   image_origin : 2;
            unsigned char   : 2;
        };
    } image_spec;
};

unsigned char * load_targa(const char * filename, GLenum &format, int &width, int &height);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _TARGA_H_ */
